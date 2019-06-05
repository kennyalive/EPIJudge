#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
    if (!L)
        return L;

    shared_ptr<ListNode<int>> before_start_node;
    auto start_node = L;
    for (int i = 1; i < start; i++) {
        before_start_node = start_node;
        start_node = start_node->next;
    }

    auto prev_node = start_node;
    auto current_node = start_node->next;

    for (int i = 0; i < finish - start; i++) {
        auto next_node = current_node->next;
        current_node->next = prev_node;
        prev_node = current_node;
        current_node = next_node;
    }
    auto finish_node = prev_node;
   
    start_node->next = current_node;
    if (before_start_node) {
        before_start_node->next = finish_node;
        return L;
    }
    else {
        return finish_node;
    }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
