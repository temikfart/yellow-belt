#pragma once

#include "date.h"

#include <map>
#include <set>
#include <memory>

enum class Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

enum class LogicalOperation {
  Or,
  And
};

class Node {
public:
  virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
  virtual ~Node() = default;
};

class EmptyNode : public Node {
public:
  EmptyNode();
  bool Evaluate(const Date& date, const std::string& event) const override;
};

class DateComparisonNode : public Node {
public:
  DateComparisonNode(const Comparison& cmp, const Date& date) ;
  bool Evaluate(const Date& date, const std::string& event) const override;

private:
  const Comparison cmp_;
  const Date date_;
};

class EventComparisonNode : public Node {
public:
  EventComparisonNode(const Comparison& cmp, const std::string& event);
  bool Evaluate(const Date& date, const std::string& event) const override;

private:
  const Comparison cmp_;
  const std::string event_;
};

class LogicalOperationNode : public Node {
public:
  LogicalOperationNode(const LogicalOperation& logical_operation,
                       const std::shared_ptr<Node>& lhs,
                       const std::shared_ptr<Node>& rhs);
  bool Evaluate(const Date& date, const std::string& event) const override;

private:
  const LogicalOperation lgc_op_;
  const std::shared_ptr<Node> lhs_node_;
  const std::shared_ptr<Node> rhs_node_;
};
