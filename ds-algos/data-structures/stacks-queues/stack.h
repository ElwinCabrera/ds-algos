#ifndef STACK_H
#define STACK_H

#include "../lists/list.h"

template<class Type, class Seq_Container = List<Type>>
class Stack{
public:
    typedef typename Seq_Container::value_type value_type;
    typedef typename Seq_Container::reference reference;
    typedef typename Seq_Container::const_reference const_reference;
    typedef typename Seq_Container::size_type size_type;
    typedef Seq_Container container_type;

    Stack() : container() {}
    Stack(const Seq_Container &cont ): container(cont) {}
    Stack(const Seq_Container &&cont) : container(std::move(cont)) { }
    Stack(const Stack &other) : container(other.container) {}
    Stack(Stack &&other) : container(std::move(other.container)) { }
    ~Stack() {}
    Stack& operator=(const Stack &other);
    Stack& operator=(Stack &&other);

    //Element access
    reference top() { return container.back(); }
    const_reference top() const { return container.back();}

    //Capacity
    bool empty() const { return container.empty(); }
    size_type size() const {return container.size(); }

    //Modifiers
    void push(const value_type &value) { container.push_back(value);}
    void push(value_type &&value) { container.push_back(std::move(value)); }
    //template<class... Args>
    //void emplace(Args&&... args);
    void pop() { container.pop_back(); }
    void swap(Stack &other) noexcept;

    //Non-member functions
    // template<typename T, typename Container>
	// friend bool operator==(const Stack<T, Container>& st1, const stack<T, Container>& st2);
    // template<typename T, typename Container>
	// friend bool operator!=(const Stack<T, Container>& st1, const stack<T, Container>& st2);
    // template<typename T, typename Container>
	// friend bool operator<(const Stack<T, Container>& st1, const stack<T, Container>& st2);
    // template<typename T, typename Container>
	// friend bool operator<=(const Stack<T, Container>& st1, const stack<T, Container>& st2);
    // template<typename T, typename Container>
	// friend bool operator>(const Stack<T, Container>& st1, const stack<T, Container>& st2);
    // template<typename T, typename Container>
	// friend bool operator>=(const Stack<T, Container>& st1, const stack<T, Container>& st2);

    template<typename T, typename Container>
    friend std::ostream& operator<<(std::ostream &os, const Stack<T, Container> &st) {
        //auto l = Container;
        List<Type> l = st.container;
        os.put('_');
        os.put('_');
        os.put('_');
        os.put('_');
        os.put('\n');
        for (auto it = l.end()-1; it != l.begin()-1; --it) {
            
            if(it == l.end()-1) {
                os << it->data << " <- Top\n";
            } else os << it->data << "\n";
        }
        os.put('_');
        os.put('_');
        os.put('_');
        os.put('_');

        return os ;
    }


protected:
    Seq_Container container;
};

#endif // STACK_H