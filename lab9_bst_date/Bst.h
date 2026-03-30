#ifndef BST_H
#define BST_H

#include <iostream>

/**
 * @class Bst
 * @brief A simple recursive binary search tree template.
 *
 * Stores values of type T using binary search tree ordering.
 * Duplicate values are not inserted.
 *
 * @tparam T The data type stored in the tree. Type T must support
 * comparison operators <, >, and ==. If traversal output is used,
 * type T must also support the output operator <<.
 */
template <class T>
class Bst
{
public:
    /**
     * @brief Default constructor.
     */
    Bst();

    /**
     * @brief Copy constructor.
     * @param other Tree to copy from.
     */
    Bst(const Bst<T>& other);

    /**
     * @brief Destructor.
     */
    ~Bst();

    /**
     * @brief Assignment operator.
     * @param other Tree to copy from.
     * @return Reference to this tree.
     */
    Bst<T>& operator=(const Bst<T>& other);

    /**
     * @brief Inserts a value into the BST.
     * @param value Value to insert.
     * @return true if inserted, false if duplicate.
     */
    bool Insert(const T& value);

    /**
     * @brief Searches for a value in the BST.
     * @param value Value to search for.
     * @return true if found, false otherwise.
     */
    bool Search(const T& value) const;

    /**
     * @brief Outputs tree contents using inorder traversal.
     */
    void InOrder() const;

    /**
     * @brief Outputs tree contents using preorder traversal.
     */
    void PreOrder() const;

    /**
     * @brief Outputs tree contents using postorder traversal.
     */
    void PostOrder() const;

    /**
     * @brief Clears the tree.
     */
    void Clear();

    /**
     * @brief Checks whether the tree is empty.
     * @return true if empty, false otherwise.
     */
    bool IsEmpty() const;

    /**
     * @brief Checks whether the BST ordering invariant holds.
     * @return true if the tree satisfies BST ordering, false otherwise.
     */
    bool CheckInvariant() const;

private:
    /**
     * @struct Node
     * @brief Internal tree node storing one data item and two child pointers.
     */
    struct Node
    {
        T data;
        Node* left;
        Node* right;
    };

    Node* m_root;

    Node* Insert(Node* node, const T& value, bool& inserted);
    bool Search(const Node* node, const T& value) const;

    void InOrder(const Node* node) const;
    void PreOrder(const Node* node) const;
    void PostOrder(const Node* node) const;

    void DeleteTree(Node* node);
    Node* CopyTree(const Node* node);

    bool CheckInvariant(const Node* node, const T* minValue, const T* maxValue) const;

};

// Implementation

template <class T>
Bst<T>::Bst()
    : m_root(nullptr)
{
}

template <class T>
Bst<T>::Bst(const Bst<T>& other)
    : m_root(CopyTree(other.m_root))
{
}

template <class T>
Bst<T>::~Bst()
{
    Clear();
}

template <class T>
Bst<T>& Bst<T>::operator=(const Bst<T>& other)
{
    if (this != &other)
    {
        Clear();
        m_root = CopyTree(other.m_root);
    }

    return *this;
}

template <class T>
bool Bst<T>::Insert(const T& value)
{
    bool inserted = false;
    m_root = Insert(m_root, value, inserted);
    return inserted;
}

template <class T>
typename Bst<T>::Node* Bst<T>::Insert(Node* node, const T& value, bool& inserted)
{
    if (node == nullptr)
    {
        Node* newNode = new Node{value, nullptr, nullptr};
        inserted = true;
        return newNode;
    }

    if (value < node->data)
    {
        node->left = Insert(node->left, value, inserted);
    }
    else if (value > node->data)
    {
        node->right = Insert(node->right, value, inserted);
    }
    else
    {
        inserted = false;
    }

    return node;
}

template <class T>
bool Bst<T>::Search(const T& value) const
{
    return Search(m_root, value);
}

template <class T>
bool Bst<T>::Search(const Node* node, const T& value) const
{
    if (node == nullptr)
    {
        return false;
    }

    if (value == node->data)
    {
        return true;
    }

    if (value < node->data)
    {
        return Search(node->left, value);
    }

    return Search(node->right, value);
}

template <class T>
void Bst<T>::InOrder() const
{
    InOrder(m_root);
}

template <class T>
void Bst<T>::InOrder(const Node* node) const
{
    if (node != nullptr)
    {
        InOrder(node->left);
        std::cout << node->data << ' ';
        InOrder(node->right);
    }
}

template <class T>
void Bst<T>::PreOrder() const
{
    PreOrder(m_root);
}

template <class T>
void Bst<T>::PreOrder(const Node* node) const
{
    if (node != nullptr)
    {
        std::cout << node->data << ' ';
        PreOrder(node->left);
        PreOrder(node->right);
    }
}

template <class T>
void Bst<T>::PostOrder() const
{
    PostOrder(m_root);
}

template <class T>
void Bst<T>::PostOrder(const Node* node) const
{
    if (node != nullptr)
    {
        PostOrder(node->left);
        PostOrder(node->right);
        std::cout << node->data << ' ';
    }
}

template <class T>
void Bst<T>::Clear()
{
    DeleteTree(m_root);
    m_root = nullptr;
}

template <class T>
void Bst<T>::DeleteTree(Node* node)
{
    if (node != nullptr)
    {
        DeleteTree(node->left);
        DeleteTree(node->right);
        delete node;
    }
}

template <class T>
bool Bst<T>::IsEmpty() const
{
    return m_root == nullptr;
}

template <class T>
typename Bst<T>::Node* Bst<T>::CopyTree(const Node* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    Node* newNode = new Node{node->data, nullptr, nullptr};
    newNode->left = CopyTree(node->left);
    newNode->right = CopyTree(node->right);
    return newNode;
}

template <class T>
bool Bst<T>::CheckInvariant() const
{
    return CheckInvariant(m_root, nullptr, nullptr);
}

template <class T>
bool Bst<T>::CheckInvariant(const Node* node, const T* minValue, const T* maxValue) const
{
    if (node == nullptr)
    {
        return true;
    }

    if ((minValue != nullptr && !(node->data > *minValue)) ||
        (maxValue != nullptr && !(node->data < *maxValue)))
    {
        return false;
    }

    return CheckInvariant(node->left, minValue, &node->data) &&
           CheckInvariant(node->right, &node->data, maxValue);
}

#endif
