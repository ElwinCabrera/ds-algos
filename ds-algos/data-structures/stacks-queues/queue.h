#ifndef QUEUE_H
#define QUEUE_H

#include "../lists/list.h"

template<class Type, class Seq_Container = List<Type>>
class Queue{
public:
    typedef typename Seq_Container::value_type value_type;
    typedef typename Seq_Container::reference reference;
    typedef typename Seq_Container::const_reference const_reference;
    typedef typename Seq_Container::size_type size_type;
    typedef Seq_Container container_type;

    Queue() : container() {}
    Queue(const Seq_Container &cont ): container(cont) {}
    Queue(const Seq_Container &&cont) : container(std::move(cont)) { }
    Queue(const Queue &other) : container(other.container) {}
    Queue(Queue &&other) : container(std::move(other.container)) { }
    ~Queue() {}
    Queue& operator=(const Queue &other);
    Queue& operator=(Queue &&other);

    //Element access
    reference front() { return container.front(); }
    const_reference front() const { return container.front();}

    reference back() { return container.back(); }
    const_reference back() const { return container.back();}

    //Capacity
    bool empty() const { return container.empty(); }
    size_type size() const {return container.size(); }

    //Modifiers
    void push(const value_type &value) { container.push_back(value);}
    void push(value_type &&value) { container.push_back(std::move(value)); }
    //template<class... Args>
    //void emplace(Args&&... args);
    void pop() { container.pop_front(); }
    void swap(Queue &other) noexcept;

    //Non-member functions
    // template<typename T, typename Container>
	// friend bool operator==(const Queue<T, Container>& st1, const Queue<T, Container>& st2);
    // template<typename T, typename Container>
	// friend bool operator!=(const Queue<T, Container>& st1, const Queue<T, Container>& st2);
    // template<typename T, typename Container>
	// friend bool operator<(const Queue<T, Container>& st1, const Queue<T, Container>& st2);
    // template<typename T, typename Container>
	// friend bool operator<=(const Queue<T, Container>& st1, const Queue<T, Container>& st2);
    // template<typename T, typename Container>
	// friend bool operator>(const Queue<T, Container>& st1, const Queue<T, Container>& st2);
    // template<typename T, typename Container>
	// friend bool operator>=(const Queue<T, Container>& st1, const Queue<T, Container>& st2);

    template<typename T, typename Container>
    friend std::ostream& operator<<(std::ostream &os, const Queue<T, Container> &st) {
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

#endif // QUEUE_H