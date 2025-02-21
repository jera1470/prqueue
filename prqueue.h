#pragma once

#include <iostream>  // For debugging
#include <sstream>   // For as_string

using std::ostream, std::ostringstream, std::string, std::endl;

template <typename T>
class prqueue {
   private:
    struct NODE {
        int priority;
        T value;
        NODE* parent;
        NODE* left;
        NODE* right;
        NODE* link;  // Link to duplicates -- Part 2 only
    };

    NODE* root;
    size_t sz;

    // Utility pointers for begin and next.
    NODE* curr;
    NODE* temp;  // Optional

    // TODO_STUDENT: add private helper function definitions here

    // Creates a new node with the given value and priority.
    NODE* helper_create_node(T value, int priority) {
        NODE* new_node = new NODE;
        new_node->value = value;
        new_node->priority = priority;
        new_node->parent = nullptr;
        new_node->left = nullptr;
        new_node->right = nullptr;
        new_node->link = nullptr;
        sz++;
        return new_node;
    }

    // Deletes the given node and all of its children.
    void helper_delete_node(NODE* node) {
        if (node == nullptr) {
            return;
        }

        // Delete duplicates
        if (node->link != nullptr) {
            helper_delete_node(node->link);
        }

        // Recursrively delete children, first to the left and then the right
        helper_delete_node(node->left);
        helper_delete_node(node->right);
        delete node;
    }

    // Returns the node with the smallest priority
    NODE* helper_min_priority_node(NODE* node) const {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->left == nullptr) {
            return node;
        }
        return helper_min_priority_node(node->left);
    }

    // Removes the node with the smallest priority
    void helper_remove_min_priority_node(NODE* node) {
        NODE* par = nullptr;
        curr = root;
        while (curr != nullptr) {
            // Check if curr is the node we want to remove
            if (curr->priority == node->priority) {
                // check if there is a link/duplicate
                if (curr->link != nullptr) {
                    temp = curr;
                    curr = curr->link;
                    // If parent is nullptr, then we are at the root
                    if (par == nullptr) {
                        root = curr;
                    }
                    // If parent is not nullptr, then we are not at the root
                    else{
                        curr->parent = par;
                        if (par->left == temp) {
                            par->left = curr;
                        }
                        else if (par->right == temp) {
                            par->right = curr;
                        }
                    }
                    if (temp->left != nullptr) {
                        curr->left = temp->left;
                        curr->left->parent = curr;
                    }
                    if (temp->right != nullptr) {
                        curr->right = temp->right;
                        curr->right->parent = curr;
                    }
                    delete temp;
                    temp = nullptr;
                    sz--;
                }
                else if (curr->left == nullptr && curr->right == nullptr) {
                    if (par == nullptr) {
                        root = nullptr;
                    } else if (par->left == curr) {
                        par->left = nullptr;
                    } else {
                        par->right = nullptr;
                    }
                    delete curr;
                    curr = nullptr;
                    sz--;
                }
                else if (curr->left == nullptr) {
                    if (par == nullptr) {
                        root = curr->right;
                        root->parent = nullptr;
                    } else if (par->left == curr) {
                        par->left = curr->right;
                        par->left->parent = par;
                    } else {
                        par->right = curr->right;
                        par->right->parent = par;
                    }
                    delete curr;
                    curr = nullptr;
                    sz--;
                }
                else if (curr->right == nullptr) {
                    if (par == nullptr) {
                        root = curr->left;
                        root->parent = nullptr;
                    } else if (par->left == curr) {
                        par->left = curr->left;
                        par->left->parent = par;
                    } else {
                        par->right = curr->left;
                        par->right->parent = par;
                    }
                    delete curr;
                    curr = nullptr;
                    sz--;
                }
                else {
                    NODE* suc = curr->right;
                    while (suc->left != nullptr) {
                        suc = suc->left;
                    }
                    NODE* sucData = helper_create_node(suc->value, suc->priority);
                    helper_remove_min_priority_node(suc);
                    curr->value = sucData->value;
                    curr->priority = sucData->priority;
                }
                return;
            }
            // If curr is not the node we want to remove, go left or right
            else if (curr->priority > node->priority) {
                par = curr;
                curr = curr->left;
            }
            else if(curr->priority < node->priority) {
                par = curr;
                curr = curr->right;
            }
        }
    }

    // Prints the tree in order
    void helper_print_tree(NODE* node, ostream& os) const {
        if (node == nullptr) {
            return;
        }

        // Print left, then the duplicates in there, right
        helper_print_tree(node->left, os);
        os << node->priority << " value: " << node->value << endl;
        if (node->link != nullptr) {
            for (NODE* curr = node->link; curr != nullptr; curr = curr->link) {
                os << curr->priority << " value: " << curr->value << endl;
            }
        }
        helper_print_tree(node->right, os);
    }

    // Copies the tree in order and recursively creates new nodes
    NODE* helper_copy_tree(NODE* node, NODE* parent = nullptr) {
        if (node == nullptr) {
            return nullptr;
        }

        NODE* newNode = helper_create_node(node->value, node->priority);
        newNode->parent = parent;
        newNode->left = helper_copy_tree(node->left, newNode);
        if (node->link != nullptr) {
            newNode->link = helper_copy_tree(node->link, nullptr);
        }
        newNode->right = helper_copy_tree(node->right, newNode);

        return newNode;
    }

    // Checks if two trees are identical in value and priority as well as the form of the tree
    bool isIdentical(NODE* node1, NODE* node2) const {
        if (node1 == nullptr && node2 == nullptr) {
            return true;
        }

        else if (node1 == nullptr || node2 == nullptr) {
            return false;
        }

        else if (node1->link != nullptr && node2->link != nullptr) {
            return isIdentical(node1->link, node2->link) && ((node1->priority == node2->priority) && isIdentical(node1->left, node2->left) && isIdentical(node1->right, node2->right));;

        }

        else{
            return (node1->priority == node2->priority) && isIdentical(node1->left, node2->left) && isIdentical(node1->right, node2->right);
        }
    }

   public:
    /// Creates an empty `prqueue`.
    ///
    /// Runs in O(1).
    prqueue() {
        sz = 0;
        root = nullptr;
        curr = nullptr;
        temp = nullptr;
    }

    /// Copy constructor.
    ///
    /// Copies the value-priority pairs from the provided `prqueue`.
    /// The internal tree structure must be copied exactly.
    ///
    /// Runs in O(N), where N is the number of values in `other`.
    prqueue(const prqueue& other) {
        root = helper_copy_tree(other.root);
        sz = other.size();
    }

    /// Assignment operator; `operator=`.
    ///
    /// Clears `this` tree, and copies the value-priority pairs from the
    /// provided `prqueue`. The internal tree structure must be copied exactly.
    ///
    /// Runs in O(N + O), where N is the number of values in `this`, and O is
    /// the number of values in `other`.
    prqueue& operator=(const prqueue& other) {
        if (this != &other) {
            clear();
            root = helper_copy_tree(other.root);
            sz = other.size();
        }
        return *this;
    }

    /// Empties the `prqueue`, freeing all memory it controls.
    ///
    /// Runs in O(N), where N is the number of values.
    void clear() {
        helper_delete_node(root);
        root = nullptr;
        curr = nullptr;
        temp = nullptr;
        sz = 0;
    }

    /// Destructor, cleans up all memory associated with `prqueue`.
    ///
    /// Runs in O(N), where N is the number of values.
    ~prqueue() {
        clear();
    }

    /// Adds `value` to the `prqueue` with the given `priority`.
    ///
    /// Uses the priority to determine the location in the underlying tree.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    void enqueue(T value, int priority) {
        curr = root;
        temp = nullptr;
        if (root == nullptr) {
            root = helper_create_node(value, priority);
            return;
        }
        while (curr!= nullptr) {
            if (curr->priority > priority) {
                if (curr->left == nullptr) {
                    curr->left = helper_create_node(value, priority);
                    curr->left->parent = curr;
                    return;
                }
                curr = curr->left;
            }
            else if (curr->priority < priority) {
                if (curr->right == nullptr) {
                    curr->right = helper_create_node(value, priority);
                    curr->right->parent = curr;
                    return;
                }
                curr = curr->right;
            }
            else {
                if (curr->link == nullptr) {
                    curr->link = helper_create_node(value, priority);
                    return;
                }
                else {
                    while (curr->link != nullptr) {
                        curr = curr->link;
                    }
                    curr->link = helper_create_node(value, priority);
                    return;
                }
            }
        }
    }

    /// Returns the value with the smallest priority in the `prqueue`, but does
    /// not modify the `prqueue`.
    ///
    /// If the `prqueue` is empty, returns the default value for `T`.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    T peek() const {
        if (root == nullptr) {
            return T();
        }
        NODE* min_node = helper_min_priority_node(root);
        return min_node->value;
    }

    /// Returns the value with the smallest priority in the `prqueue` and
    /// removes it from the `prqueue`.
    ///
    /// If the `prqueue` is empty, returns the default value for `T`.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    T dequeue() {
        if (root == nullptr) {
            return T();
        }

        NODE *min_node = helper_min_priority_node(root);
        T value = min_node->value;
        helper_remove_min_priority_node(min_node);
        return value;
    }

    /// Returns the number of elements in the `prqueue`.
    ///
    /// Runs in O(1).
    size_t size() const {
        return sz;
    }

    /// Resets internal state for an iterative inorder traversal.
    ///
    /// See `next` for usage details.
    ///
    /// O(H), where H is the maximum height of the tree.
    void begin() {
        temp = nullptr;
        curr = helper_min_priority_node(root);
    }

    /// Uses the internal state to return the next in-order value and priority
    /// by reference, and advances the internal state. Returns true if the
    /// reference parameters were set, and false otherwise.
    ///
    /// Example usage:
    ///
    /// ```c++
    /// pq.begin();
    /// T value;
    /// int priority;
    /// while (pq.next(value, priority)) {
    ///   cout << priority << " value: " << value << endl;
    /// }
    /// ```
    ///
    /// Runs in worst-case O(H + M) or O(H), depending on implementation, where
    /// H is the height of the tree, and M is the number of duplicate
    /// priorities.
    bool next(T& value, int& priority) {
        if (curr == nullptr) {
            return false;
        }

        value = curr->value;
        priority = curr->priority;

        if (curr->link != nullptr) {
            if (temp == nullptr) {
                temp = curr;
                curr = curr->link;
                return true;
            }
            else if (curr->parent == nullptr) {
                curr = curr->link;
                return true;
            }
        }
        else if (curr->link == nullptr) {
            if (temp != nullptr) {
                curr = temp;
            }
        }

        if (curr->right != nullptr) {
            curr = curr->right;
            while (curr->left != nullptr) {
                curr = curr->left;
            }
            temp = nullptr;
        }
        else if (curr->parent != nullptr) {
            temp = nullptr;
            while (curr->parent != nullptr && curr->parent->right == curr) {
                curr = curr->parent;
            }
            curr = curr->parent;
        }

        return true;
    }

    /// Converts the `prqueue` to a string representation, with the values
    /// in-order by priority.
    ///
    /// Example:
    ///
    /// ```c++
    /// prqueue<string> names;
    /// names.enqueue("Gwen", 3);
    /// names.enqueue("Jen", 2);
    /// names.enqueue("Ben", 1);
    /// names.enqueue("Sven", 2);
    /// ```
    ///
    /// Calling `names.as_string()` would return the following multi-line
    /// string:
    ///
    /// ```text
    /// 1 value: Ben
    /// 2 value: Jen
    /// 2 value: Sven
    /// 3 value: Gwen
    /// ```
    ///
    /// Runs in O(N), where N is the number of values.
    string as_string() const {
        ostringstream os;
        helper_print_tree(root, os);
        return os.str();
    }

    /// Checks if the contents of `this` and `other` are equivalent.
    ///
    /// Two `prqueues` are equivalent if they have the same priorities and
    /// values, as well as the same internal tree structure.
    ///
    /// These two `prqueue`s would be considered equivalent, because
    /// they have the same internal tree structure:
    ///
    /// ```c++
    /// prqueue<string> a;
    /// a.enqueue("2", 2);
    /// a.enqueue("1", 1);
    /// a.enqueue("3", 3);
    /// ```
    ///
    /// and
    ///
    /// ```c++
    /// prqueue<string> b;
    /// a.enqueue("2", 2);
    /// a.enqueue("3", 3);
    /// a.enqueue("1", 1);
    /// ```
    ///
    /// While this `prqueue`, despite containing the same priority-value pairs,
    /// would not be considered equivalent, because the internal tree structure
    /// is different.
    ///
    /// ```c++
    /// prqueue<string> c;
    /// a.enqueue("1", 1);
    /// a.enqueue("2", 2);
    /// a.enqueue("3", 3);
    /// ```
    ///
    /// Runs in O(N) time, where N is the maximum number of nodes in
    /// either `prqueue`.
    ///
    bool operator==(const prqueue& other) const {
        return isIdentical(root, other.root);
    }

    /// Returns a pointer to the root node of the BST.
    ///
    /// Used for testing the internal structure of the BST. Do not edit or
    /// change.
    ///
    /// Runs in O(1).
    void* getRoot() {
        return root;
    }
};
