#include <functional>
#include <mutex>
#include <memory>

template <typename T, typename... ARGS>
class lockable{
public:
	lockable(ARGS&&... args) :
		value(new T(std::forward<ARGS>(args)...)),
		mutex(new std::recursive_mutex()){
	}

	T *operator ->(){
		return value.get();
	}
	void lock(std::function<void()> block){
		std::unique_lock<std::recursive_mutex> guard(*mutex.get());
			block();
	}

	lockable(lockable<T,ARGS...> &&o){
		value = std::move(o.value);
		mutex = std::move(o.mutex);
	}
	lockable<T,ARGS...> &operator =(lockable<T,ARGS...> &&o){
		value = std::move(o.value);
		mutex = std::move(o.mutex);
	}

private:
	lockable(const lockable<T,ARGS...> &o) = delete;
	lockable &operator =(const lockable<T,ARGS...> &o) = delete;

private:
	std::unique_ptr<std::recursive_mutex> mutex;
	std::unique_ptr<T> value;
};

template <typename T, typename... ARGS>
lockable<T,ARGS...> make_lockable(ARGS&&... args){
	return lockable<T,ARGS...>(std::forward<ARGS>(args)...);
}
