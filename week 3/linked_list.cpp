#include "test_runner.h"

#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
    struct Node {
        T value;
        Node* next = nullptr;
    };

    ~LinkedList() {
        while (head != nullptr) {
            Node* obj = head;
            head = head->next;
            delete obj;
        }}

    void PushFront(const T& value) {
        Node* new_head = new Node;
        new_head->value = value;
        new_head->next = head;
        head = new_head;
    }

    void InsertAfter(Node* node, const T& value) {
        if (node == nullptr) PushFront(value);
        else {
            Node* insert_node = new Node;
            insert_node->next = node->next;
            insert_node->value = value;
            node->next = insert_node;
        }
    }
    void RemoveAfter(Node* node) {
        if (node == nullptr) {PopFront(); }
        else if (node->next == nullptr) {
            return;
        }
        else {
            Node* next_node = node->next;
            node->next = next_node->next;
            delete next_node;
        }
    }
    void PopFront() {
        if (head == nullptr) {
            return;
        }

        if (head != nullptr)  {
            Node* new_head = head;
            head = head->next;
            delete new_head;
        }

    }

    Node* GetHead() { return head; }
    const Node* GetHead() const { return head; }

private:
    Node* head = nullptr;
};

template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
    vector<T> result;
    for (auto node = list.GetHead(); node; node = node->next) {
        result.push_back(node->value);
    }
    return result;
}

void TestPushFront() {
    LinkedList<int> list;

    list.PushFront(1);
    ASSERT_EQUAL(list.GetHead()->value, 1);
    list.PushFront(2);
    ASSERT_EQUAL(list.GetHead()->value, 2);
    list.PushFront(3);
    ASSERT_EQUAL(list.GetHead()->value, 3);

    const vector<int> expected = {3, 2, 1};
    ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
    LinkedList<string> list;

    list.PushFront("a");
    auto head = list.GetHead();
    ASSERT(head);
    ASSERT_EQUAL(head->value, "a");

    list.InsertAfter(head, "b");
    const vector<string> expected1 = {"a", "b"};
    ASSERT_EQUAL(ToVector(list), expected1);

    list.InsertAfter(head, "c");
    const vector<string> expected2 = {"a", "c", "b"};
    ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter() {
    LinkedList<int> list;
    for (int i = 1; i <= 5; ++i) {
        list.PushFront(i);
    }

    const vector<int> expected = {5, 4, 3, 2, 1};
    ASSERT_EQUAL(ToVector(list), expected);

    auto next_to_head = list.GetHead()->next;
    list.RemoveAfter(next_to_head); // СѓРґР°Р»СЏРµРј 3
    list.RemoveAfter(next_to_head); // СѓРґР°Р»СЏРµРј 2

    const vector<int> expected1 = {5, 4, 1};
    ASSERT_EQUAL(ToVector(list), expected1);

    while (list.GetHead()->next) {
        list.RemoveAfter(list.GetHead());
    }
    ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
    LinkedList<int> list;

    for (int i = 1; i <= 5; ++i) {
        list.PushFront(i);
    }
    for (int i = 1; i <= 5; ++i) {
        list.PopFront();
    }
    ASSERT(list.GetHead() == nullptr);
}

void TestRemoveNullptr() {
    LinkedList<int> list;
    list.PushFront(1);
    auto head = list.GetHead();
    list.RemoveAfter(head);
    ASSERT(list.GetHead() == head);
}

void TestPopFrontEmptyList() {
    LinkedList<int> list;
    list.PopFront();
    list.PushFront(1);
    list.PopFront();
    list.PushFront(2);
    list.RemoveAfter(list.GetHead());
    ASSERT(list.GetHead()->value == 2);
}


int main() {
    TestRunner tr;
    RUN_TEST(tr, TestPushFront);
    RUN_TEST(tr, TestInsertAfter);
    RUN_TEST(tr, TestRemoveAfter);
    RUN_TEST(tr, TestPopFront);
    RUN_TEST(tr, TestRemoveNullptr);
    RUN_TEST(tr, TestPopFrontEmptyList);
    return 0;
}
