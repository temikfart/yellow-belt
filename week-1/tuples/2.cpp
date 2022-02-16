#include <iostream>
#include <vector>
#include <tuple>
#include <map>

using namespace std;

#define LOCAL
#ifdef LOCAL
// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};
#endif

// Выделим в отдельную функцию получение следующего по приоритету типа задачи
// Функция налагает требование на входной параметр: он не должен быть равен DONE
// При этом task_status явно не сравнивается с DONE, что позволяет
// сделать эту функцию максимально эффективной
TaskStatus Next(TaskStatus task_status) {
  return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

#ifdef LOCAL
// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;
#endif

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const;
  
  // Добавить новую задачу (в статусе NEW) для конкретного разработчика
  void AddNewTask(const string& person);
  
  // Обновить статусы по данному количеству задач конкретного разработчика
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
    const string& person, int task_count);

private:
  map<string, TasksInfo> person_tasks_;
};

const TasksInfo& TeamTasks::GetPersonTasksInfo(const string& person) const {
  return person_tasks_.at(person);
}

void TeamTasks::AddNewTask(const string& person) {
  ++person_tasks_[person][TaskStatus::NEW];
}

// Функция для удаления нулей из словаря
void RemoveZeros(TasksInfo& tasks_info) {
  // Соберём те статусы, которые нужно убрать из словаря
  vector<TaskStatus> statuses_to_remove;
  for (const auto& task_item : tasks_info) {
    if (task_item.second == 0) {
      statuses_to_remove.push_back(task_item.first);
    }
  }
  for (const TaskStatus status : statuses_to_remove) {
    tasks_info.erase(status);
  }
}


tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(
  const string& person, int task_count) {
  TasksInfo updated_tasks, untouched_tasks;
  
  // Здесь и далее мы будем пользоваться тем фактом, что в std::map оператор []
  // в случае отсутствия ключа инициализирует значение по умолчанию,
  // если это возможно.
  // std::map::operator[] ->
  // http://ru.cppreference.com/w/cpp/container/map/operator_at
  TasksInfo& tasks = person_tasks_[person];
  
  // Посчитаем, сколько задач каждого из статусов нужно обновить,
  // пользуясь тем фактом, что по умолчанию enum class инциализирует значения
  // от нуля по возрастанию.
  // enum class -> http://ru.cppreference.com/w/cpp/language/enum
  for (TaskStatus status = TaskStatus::NEW;
       status != TaskStatus::DONE;
       status = Next(status)) {
    // Считаем обновлённые
    updated_tasks[Next(status)] = min(task_count, tasks[status]);
    // Считаем, сколько осталось обновить
    task_count -= updated_tasks[Next(status)];
  }
  
  // Обновляем статус текущих задач в соответствии с информацией об обновлённых
  // и находим количество нетронутых
  for (TaskStatus status = TaskStatus::NEW;
       status != TaskStatus::DONE;
       status = Next(status)) {
    untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
    tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
  }
  // По условию, DONE задачи не нужно возвращать в не обновлённых задачах
  tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];
  
  // По условию в словарях не должно быть нулей
  RemoveZeros(updated_tasks);
  RemoveZeros(untouched_tasks);
  RemoveZeros(person_tasks_.at(person));
  
  return {updated_tasks, untouched_tasks};
}

#ifdef LOCAL
// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
       ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
       ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
       ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  for (int i = 0; i < 5; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
  TasksInfo updated_tasks, untouched_tasks;
  
  tie(updated_tasks, untouched_tasks) =
    tasks.PerformPersonTasks("Ivan", 5);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  cout << endl;
  
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  cout << endl;
  
  tie(updated_tasks, untouched_tasks) =
    tasks.PerformPersonTasks("Ivan", 5);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  cout << endl;
  
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  cout << endl;
  
  tie(updated_tasks, untouched_tasks) =
    tasks.PerformPersonTasks("Ivan", 1);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  cout << endl;
  
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  cout << endl;
  
  for (int i = 0; i < 5; ++i) {
    tasks.AddNewTask("Ivan");
  }
  
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  cout << endl;
  
  tie(updated_tasks, untouched_tasks) =
    tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  cout << endl;
  
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  cout << endl;
  
  tie(updated_tasks, untouched_tasks) =
    tasks.PerformPersonTasks("Ivan", 4);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  cout << endl;
  
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  cout << endl;
  
  return 0;
}
#endif
