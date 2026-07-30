#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

namespace LIST {
    struct NODE {
        int val;
        NODE* next;
        NODE(int v = 0) : val(v), next(nullptr) {}
    };

    NODE* head = nullptr;
    int len = 0;

    void init() {
        head = nullptr;
        len = 0;
    }

    NODE* move(int i) {
        if (len == 0 || i < 0 || i >= len) return nullptr;
        NODE* cur = head;
        while (i--) cur = cur->next;
        return cur;
    }

    void insert(int i, int x) {
        NODE* node = new NODE(x);
        if (len == 0) {
            node->next = node;
            head = node;
            len = 1;
            return;
        }
        if (i <= 0) {
            NODE* tail = move(len - 1);
            node->next = head;
            head = node;
            tail->next = head;
            ++len;
            return;
        }
        if (i >= len) {
            NODE* tail = move(len - 1);
            tail->next = node;
            node->next = head;
            ++len;
            return;
        }
        NODE* prev = move(i - 1);
        node->next = prev->next;
        prev->next = node;
        ++len;
    }

    void remove(int i) {
        if (len == 0 || i < 0 || i >= len) return;
        if (len == 1) {
            delete head;
            head = nullptr;
            len = 0;
            return;
        }
        if (i == 0) {
            NODE* node = head;
            NODE* new_head = head->next;
            NODE* tail = move(len - 1);
            tail->next = new_head;
            head = new_head;
            delete node;
            --len;
            return;
        }
        NODE* prev = move(i - 1);
        NODE* target = prev->next;
        prev->next = target->next;
        delete target;
        --len;
    }

    void remove_insert(int i) {
        if (len <= 1 || i < 0 || i >= len) return;
        if (i == len - 1) return;
        if (i == 0) {
            NODE* node = head;
            NODE* new_head = head->next;
            NODE* tail = move(len - 1);
            head = new_head;
            tail->next = node;
            node->next = head;
            return;
        }
        NODE* tail = move(len - 1);
        NODE* prev = move(i - 1);
        NODE* node = prev->next;
        prev->next = node->next;
        tail->next = node;
        node->next = head;
    }

    void get_length() {
        cout << len << '\n';
    }

    void query(int i) {
        if (i < 0 || i >= len) {
            cout << -1 << '\n';
            return;
        }
        NODE* node = move(i);
        cout << node->val << '\n';
    }

    void get_max() {
        if (len == 0) {
            cout << -1 << '\n';
            return;
        }
        int mx = INT_MIN;
        NODE* cur = head;
        for (int k = 0; k < len; ++k) {
            mx = max(mx, cur->val);
            cur = cur->next;
        }
        cout << mx << '\n';
    }

    void clear() {
        if (len == 0) return;
        NODE* tail = move(len - 1);
        tail->next = nullptr;
        NODE* cur = head;
        while (cur) {
            NODE* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = nullptr;
        len = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_) {
        cin >> op;
        switch (op) {
            case 0:
                LIST::get_length();
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p, x);
                break;
            case 2:
                cin >> p;
                LIST::query(p);
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                cin >> p;
                LIST::remove_insert(p);
                break;
            case 5:
                LIST::get_max();
                break;
        }
    }
    LIST::clear();
    return 0;
}
