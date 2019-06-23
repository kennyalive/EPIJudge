#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include <vector>
using std::vector;

class Queue {
 public:
     vector<int> values;
     int head = 0;
     int tail = 0;
     int size = 0;

  Queue(size_t capacity) : values(capacity + 1) {}

  void Enqueue(int x) {
      if (size == (int)values.size()-1) {
          vector<int> values2((int)values.size()*2 + 1);
          int i = 0;
          while (head != tail) {
              values2[i++] = values[head++];
              if (head == (int)values.size())
                  head = 0;
          }
          values.swap(values2);
          head = 0;
          tail = size;
      }
      values[tail++] = x;
      if (tail == (int)values.size())
          tail = 0;
      size++;
  }
  int Dequeue() {
      int value = values[head];
      head++;
      if (head == values.size())
          head = 0;
      size--;
      return value;
  }
  int Size() const {
      return size;
  }
};
struct QueueOp {
  enum { kConstruct, kDequeue, kEnqueue, kSize } op;
  int argument;

  QueueOp(const std::string& op_string, int arg) : argument(arg) {
    if (op_string == "Queue") {
      op = kConstruct;
    } else if (op_string == "dequeue") {
      op = kDequeue;
    } else if (op_string == "enqueue") {
      op = kEnqueue;
    } else if (op_string == "size") {
      op = kSize;
    } else {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }

  void execute(Queue& q) const {
    switch (op) {
      case kConstruct:
        // Hack to bypass deleted assign operator
        q.~Queue();
        new (&q) Queue(argument);
        break;
      case kDequeue: {
        int result = q.Dequeue();
        if (result != argument) {
          throw TestFailure("Dequeue: expected " + std::to_string(argument) +
                            ", got " + std::to_string(result));
        }
      } break;
      case kEnqueue:
        q.Enqueue(argument);
        break;
      case kSize: {
        int s = q.Size();
        if (s != argument) {
          throw TestFailure("Size: expected " + std::to_string(argument) +
                            ", got " + std::to_string(s));
        }
      } break;
    }
  }
};

template <>
struct SerializationTraits<QueueOp> : UserSerTraits<QueueOp, std::string, int> {
};

void QueueTester(const std::vector<QueueOp>& ops) {
  Queue q(0);
  for (auto& op : ops) {
    op.execute(q);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
                         &QueueTester, DefaultComparator{}, param_names);
}
