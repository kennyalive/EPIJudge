#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
    ListNode<int> head_node_object;
    auto head_node = std::shared_ptr<ListNode<int>>(&head_node_object,
        [](ListNode<int>* p) {});
    head_node->next = L;

    auto sublist_head = head_node;
    for (int i = 1; i < start; i++)
        sublist_head = sublist_head->next;

    auto sublist_tail = sublist_head->next;

    while (start++ < finish) {
        auto node_to_move_to_sublist_head = sublist_tail->next;
        sublist_tail->next = node_to_move_to_sublist_head->next;
        node_to_move_to_sublist_head->next = sublist_head->next;
        sublist_head->next = node_to_move_to_sublist_head;
    }

    return head_node->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
