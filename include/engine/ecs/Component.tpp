
template<typename C>
int Component<C>::GetSize() {
    return sizeof(C);
}

template<typename C>
void Component<C>::MoveData(char *src, char *dst) {
    new (dst) C(std::move(*reinterpret_cast<C*>(src)));
}

template<typename C>
void Component<C>::DestroyData(char *loc) {
    // std::launder is needed here in case the underlying data structure has some const members
    C* obj = reinterpret_cast<C*>(std::launder(loc));

    // Call destructor. This destroys the object without de-allocating memory.
    obj->~C();
}

template<typename C>
void Component<C>::Initialize(char *loc) {
    new (loc) C;
}