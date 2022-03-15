#include "node.h"

using namespace std;

EmptyNode::EmptyNode() {}
bool EmptyNode::Evaluate(const Date& date,
                         const string& event) const {
  return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp,
                                       const Date& date)
  : cmp_(cmp), date_(date) {}
bool DateComparisonNode::Evaluate(const Date& date,
                                  const string& event) const {
  switch (cmp_) {
    case Comparison::Less:
      return (date < date_);
    case Comparison::LessOrEqual:
      return (date <= date_);
    case Comparison::Greater:
      return (date > date_);
    case Comparison::GreaterOrEqual:
      return (date >= date_);
    case Comparison::Equal:
      return (date == date_);
    case Comparison::NotEqual:
      return (date != date_);
    default:
      return false;
  }
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp,
                                         const string& event)
  : cmp_(cmp), event_(event) {}
bool EventComparisonNode::Evaluate(const Date& date,
                                   const string& event) const {
  switch (cmp_) {
    case Comparison::Less:
      return event < event_;
    case Comparison::LessOrEqual:
      return event <= event_;
    case Comparison::Greater:
      return event > event_;
    case Comparison::GreaterOrEqual:
      return event >= event_;
    case Comparison::Equal:
      return event == event_;
    case Comparison::NotEqual:
      return event != event_;
    default:
      return false;
  }
}

LogicalOperationNode::LogicalOperationNode(
  const LogicalOperation& logical_operation,
  const shared_ptr<Node>& lhs,
  const shared_ptr<Node>& rhs)
  : lgc_op_(logical_operation), lhs_node_(lhs), rhs_node_(rhs) {}
bool LogicalOperationNode::Evaluate(const Date& date,
                                    const string& event) const {
  switch (lgc_op_) {
    case LogicalOperation::Or:
      return (lhs_node_->Evaluate(date, event)
        || rhs_node_->Evaluate(date, event));
    case LogicalOperation::And:
      return (lhs_node_->Evaluate(date, event)
        && rhs_node_->Evaluate(date, event));
    default:
      return false;
  }
}
