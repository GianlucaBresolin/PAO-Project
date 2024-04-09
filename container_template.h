#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include <type_traits>
#include <stdexcept>

template <class T>
class Container{
    private:
        class item{
            public:
                T info;
                item* next;
                item(const T& val, item* p=nullptr): info(val), next(p){};   
        };
        item* first;
        item* last;
        
        static void destroy(item* p){
            if (p){
                destroy(p->next);
                delete p;
            }
        };

        static void clear(item* p){
            if(p){
                delete p->info;
                clear(p->next);
            }
        }

        static void copy(item* fst, item*& f, item*& l){
            if(!fst) {
                f=l=nullptr; 
                return;
            }
            item* ptr = fst;
            l=f=new item(ptr->info,nullptr);
            while(ptr->next) {
                ptr = ptr->next;
                l->next = new item(ptr->info, nullptr);
                l=l->next;
            }
        };
  
    public:
        Container(): first(0), last(0){};
        Container(const Container&);
        ~Container();
        void clear_no_garbage() const;
        bool empty() const;
        void add(const T&);
        T pop();
        T remove(const T&);
        T* search(const T&) const;

        class const_iterator{
            friend class Container<T>;
            private:
                const item* ptr;
                bool pastTheEnd;
                const_iterator(const item* p, bool pte=false):ptr(p), pastTheEnd(pte){};
            public:
                const_iterator():ptr(0), pastTheEnd(false){}
                const_iterator operator++(int);
                const_iterator& operator++();
                const T& operator*() const;
                const T* operator&() const;
                bool operator==(const const_iterator&) const;
                bool operator!=(const const_iterator&) const;
        };
        const_iterator begin() const;
        const_iterator end() const;
};

template <class T>
Container<T>::Container(const Container& q): first(nullptr), last(nullptr){
    copy(q.first, first, last);
}

template <class T>
Container<T>::~Container(){
    if (first){
        destroy(first);
        first=last=nullptr;
    }    
}

template <class T>
void Container<T>::clear_no_garbage() const{
    if(first)
        clear(first);
};

template <class T>
bool Container<T>::empty() const{
    return !first? true : false;
}

template <class T>
void Container<T>::add(const T& val){
    if (empty()){
        first=new item(val, first);
        last=first;
    }
    else{
        last->next=new item(val, last->next);
        last=last->next;
    }
}

template <class T>
T Container<T>::pop(){
    if (first){
        item* tmp=first;
        first=first->next;
        if (!first) 
            last=first;
        T val=tmp->info;
        delete tmp;
        return val;
    }
}

template <class T>
T Container<T>::remove(const T& t){
    item* tmp=first;
    item* past=nullptr;
    if(first){
        while(tmp->info!=t && tmp!=last){
            past=tmp;
            tmp=tmp->next;
        }
        if(tmp->info==t){
            if(tmp==first){
                first=tmp->next;
            }
            else if(tmp==last){
                    past->next=tmp->next;
                    last=past;
                }
                else{
                    past->next=tmp->next;
                }
            T removedInfo = tmp->info;
            delete tmp;
            return removedInfo;
        }
    }
    throw std::runtime_error("Element not found in the list");
}

template <class T>
T* Container<T>::search(const T& o) const{
    if(first){
        item* tmp=first;
        if (std::is_pointer<T>::value){
            while(tmp){
                if(*(tmp->info)==*o){
                    return &(tmp->info);
                }
            tmp=tmp->next;
            }
        } 
        else{
            while(tmp){
                if (tmp->info==o){
                    return &(tmp->info);
                }
            tmp=tmp->next;
            }
        }
    }
    return nullptr;
}

template <class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator++(int){       //postfisso
    const_iterator tmp(*this);
    if(ptr && !pastTheEnd){
        if (ptr->next==nullptr){
            ptr+=1;
            pastTheEnd=true;
        }
        else ptr=ptr->next;
    }
    return tmp;
}

template <class T>                
typename Container<T>::const_iterator& Container<T>::const_iterator::operator++(){
    if(ptr && !pastTheEnd){
        if (ptr->next==nullptr){
            ptr+=1;
            pastTheEnd=true;
        }
        else ptr=ptr->next;
    }
    return *this;
}

template <class T>
const T& Container<T>::const_iterator::operator*() const{
    return ptr->info;
}

template <class T>
const T* Container<T>::const_iterator::operator&() const{
    return &(ptr->info);
}

template <class T>
bool Container<T>::const_iterator::operator==(const const_iterator& it) const{
    return ptr==it.ptr;
}

template <class T>
bool Container<T>::const_iterator::operator!=(const const_iterator& it) const{
    return ptr!=it.ptr;
}

template <class T>
typename Container<T>::const_iterator Container<T>::begin() const{
    if (first) return const_iterator(first);
    else return const_iterator();
}

template <class T>
typename Container<T>::const_iterator Container<T>::end() const{
    if(!first) return const_iterator();
    else return const_iterator(last+1, true);
}

#endif
