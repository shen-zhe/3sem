

template <class T1, class T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T1, typename T2>
bool pairLessEqual(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) {
    if ((lhs.first <= rhs.first) && (lhs.second <= rhs.second)) {
        return true;
    }
    return false;
}

template <typename T1, typename T2>
bool pairGreaterEqual(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) {
    if ((lhs.first >= rhs.first) && (lhs.second >= rhs.second)) {
        return true;
    }
    return false;
} 

template <class Key, class Value>
class RedBlackTree {
private:
    enum Color { RED, BLACK };

    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        Node* parent;
        Color color;

        Node(const Key& k, const Value& v, Node* l, Node* r, Node* p, Color c)
            : key(k), value(v), left(l), right(r), parent(p), color(c) {}
    };

    Node* root;

    // Приватные методы реализации
    void leftRotate(Node* x);
    void rightRotate(Node* y);
    void insertFixup(Node* z);
    void transplant(Node* u, Node* v);
    void deleteFixup(Node* x);
    void destroyTree(Node* node);
    int depth(Node* node) const;
    void printTree(Node* node, std::string prefix, bool isLeft) const;
    void searchByFirstLetterHelper(Node* node, const char letter, std::vector<Key>& resultKeys) const;

    bool searchByValueHelper(Node* node, const Value& value, Key& resultKey) const;

    void searchInRangeHelper(Node* node, const std::pair<Key, Key>& range, std::vector<Key>& resultKeys) const {
        if (node == nullptr) {
            return;
        }

        if (pairGreaterEqual(node->key, range.first) && pairLessEqual(node->key, range.second)) {
            resultKeys.push_back(node->key);
        }

        searchInRangeHelper(node->left, range, resultKeys);
        searchInRangeHelper(node->right, range, resultKeys);
    }
    

    
    

public:
    RedBlackTree() : root(nullptr) {}

    // Публичные методы
    void insert(const Key& key, const Value& value);
    bool search(const Key& key, Value& result) const;
    bool remove(const Key& key);
    void printTree() const;
    int depth() const;
    bool searchByFirstLetter(const char letter, std::vector<Key>& resultKeys) const;
    
    bool searchByValue(const Value& value, Key& resultKey) const {
        return searchByValueHelper(root, value, resultKey);
    }

    void searchInRange(const std::pair<Key, Key>& range) const {
        std::vector<Key> resultKeys;
        searchInRangeHelper(root, range, resultKeys);

        if(resultKeys.empty()) {
            std::cout << "Нет слов в заданном диапазоне координат." << std::endl;
        } else {
            std::cout << "Слова в заданном диапазоне координат:" << std::endl;
            for (const auto& key : resultKeys) {
                Value word;
                search(key, word);
                std::cout << "Координаты: (" << key.first << ", " << key.second << "), Слово: "<< word << std::endl;
            }
        }
    }
    

    ~RedBlackTree();
    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        Iterator& operator++();
        std::pair<const Key&, Value&> operator*() const;
        bool operator!=(const Iterator& other) const;
    };
    

    Iterator begin() const;
    Iterator end() const;
};



template <class Key, class Value>
bool RedBlackTree<Key, Value>::searchByFirstLetter(const char letter, std::vector<Key>& resultKeys) const {
    resultKeys.clear();
    searchByFirstLetterHelper(root, letter, resultKeys);
    return !resultKeys.empty();
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::searchByFirstLetterHelper(Node* node, const char letter, std::vector<Key>& resultKeys) const {
    if (node == nullptr) {
        return;
    }

    searchByFirstLetterHelper(node->left, letter, resultKeys);

    if (node->key.first == letter) { // Проверяем, начинается ли слово с заданной буквы
        resultKeys.push_back(node->key);
    }

    searchByFirstLetterHelper(node->right, letter, resultKeys);
}



template <class Key, class Value>
bool RedBlackTree<Key, Value>::searchByValueHelper(Node* node, const Value& value, Key& resultKey) const {
    if (node == nullptr) {
        // Достигнут конец ветви, значение не найдено
        return false;
    }

    if (node->value.compare(value) == 0) {
        // Найдено значение, сохраняем ключ и возвращаем true
        resultKey = node->key;
        return true;
    }

    // Рекурсивный поиск в левом и правом поддеревьях
    if (searchByValueHelper(node->left, value, resultKey)) {
        return true;
    }

    return searchByValueHelper(node->right, value, resultKey);
}

template <class Key, class Value>
typename RedBlackTree<Key, Value>::Iterator RedBlackTree<Key, Value>::begin() const {
    Node* minNode = root;
    while (minNode != nullptr && minNode->left != nullptr) {
        minNode = minNode->left;
    }
    return Iterator(minNode);
}

template <class Key, class Value>
typename RedBlackTree<Key, Value>::Iterator RedBlackTree<Key, Value>::end() const {
    return Iterator(nullptr);
}

template <class Key, class Value>
typename RedBlackTree<Key, Value>::Iterator& RedBlackTree<Key, Value>::Iterator::operator++() {
    if (current == nullptr) {
        return *this;
    }

    // Если есть правый потомок, идем вправо и затем налево до конца
    if (current->right != nullptr) {
        current = current->right;
        while (current->left != nullptr) {
            current = current->left;
        }
    } else {
        // В противном случае идем вверх по дереву
        Node* parent = current->parent;
        while (parent != nullptr && current == parent->right) {
            current = parent;
            parent = parent->parent;
        }
        // Если мы поднимаемся из правого поддерева, просто перейдем к родителю
        // Если мы поднимаемся из левого поддерева, это может быть начало следующего уровня
        current = parent;
    }

    return *this;
}

template <class Key, class Value>
std::pair<const Key&, Value&> RedBlackTree<Key, Value>::Iterator::operator*() const {
    return std::pair<const Key&, Value&>(current->key, current->value);
}

template <class Key, class Value>
bool RedBlackTree<Key, Value>::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}


template <class Key, class Value>
void RedBlackTree<Key, Value>::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != nullptr) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::insertFixup(Node* z) {
    while (z->parent != nullptr && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::insert(const Key& key, const Value& value) {
    Node* z = new Node(key, value, nullptr, nullptr, nullptr, RED);
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == nullptr) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    insertFixup(z);
}

template <class Key, class Value>
bool RedBlackTree<Key, Value>::search(const Key& key, Value& result) const {
    Node* current = root;
    while (current != nullptr) {
        if (key == current->key) {
            result = current->value;
            return true;  // Найден элемент с заданным ключом
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return false;  // Элемент с заданным ключом не найден
}


template <class Key, class Value>
bool RedBlackTree<Key, Value>::remove(const Key& key) {
    Node* z = root;
    while (z != nullptr && z->key != key) {
        if (key < z->key) {
            z = z->left;
        } else {
            z = z->right;
        }
    }

    if (z == nullptr) {
        return false;  // Элемент с заданным ключом не найден
    }

    Node* y = z;
    Node* x;
    Color yOriginalColor = y->color;

    if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = z->right;
        while (y->left != nullptr) {
            y = y->left;
        }
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (yOriginalColor == BLACK) {
        deleteFixup(x);
    }

    return true;  // Элемент успешно удален
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::transplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    if (v != nullptr) {
        v->parent = u->parent;
    }
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::deleteFixup(Node* x) {
    while (x != root && (x == nullptr || x->color == BLACK)) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == nullptr || w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            // Зеркально симметричный случай для правого поддерева
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if ((w->right == nullptr || w->right->color == BLACK) &&
                (w->left == nullptr || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == nullptr || w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }

    if (x != nullptr) {
       x->color = BLACK;
    }
}


template <class Key, class Value>
int RedBlackTree<Key, Value>::depth() const {
    return depth(root);
}

template <class Key, class Value>
int RedBlackTree<Key, Value>::depth(Node* node) const {
    if (node == nullptr) {
        return 0;
    } else {
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return 1 + std::max(leftDepth, rightDepth);
    }
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::printTree() const {
    printTree(root, "", true);
}


template <class Key, class Value>
void RedBlackTree<Key, Value>::printTree(Node* node, std::string prefix, bool isLeft) const {
    if (node != nullptr) {
        if (node != nullptr) {
            std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──");
        std::cout << "(" << node->key << "," << node->value << ")"<< " (Цвет: " << (node->color == RED ? "КРАСНЫЙ" : "ЧЕРНЫЙ") << ")"  << std::endl;

        printTree(node->left, prefix + (isLeft ? "│   " : "    "), true);
        printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
        }
    }
}



template <class Key, class Value>
RedBlackTree<Key, Value>::~RedBlackTree() {
    destroyTree(root);
}

template <class Key, class Value>
void RedBlackTree<Key, Value>::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

