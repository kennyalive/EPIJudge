#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
    shared_ptr<ListNode<int>> head, tail;
    head = (L1 && L2) ? (L1->data < L2->data ? L1 : L2) : (L1 ? L1 : L2);
    if (head == L1)
        L1 = L1->next;
    else
        L2 = L2->next;
    tail = head;
    while (L1 || L2) {
        if (L1 && L2) {
            if (L1->data < L2->data) {
                tail->next = L1;
                tail = L1;
                L1 = L1->next;
            }
            else {
                tail->next = L2;
                tail = L2;
                L2 = L2->next;
            }
        }
        else if (L1) {
            tail->next = L1;
            L1 = nullptr;
        }
        else {
            tail->next = L2;
            L2 = nullptr;
        }
    }
    return head;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
