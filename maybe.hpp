#include <type_traits>
#include <variant>
#include <iostream>

template <typename T>
class Maybe {
private:
    T m_value;
    bool m_valid;

public:
    using type = T;
    Maybe(T t): m_value(t), m_valid(true) {}
    Maybe(): m_valid(false) {}
    Maybe(Maybe const & rhs) = default;
    Maybe(Maybe && rhs) noexcept = default;
    ~Maybe() = default;
    Maybe operator= (Maybe const & rhs) {
        *this = rhs;
        return *this;
    }
    Maybe operator= (Maybe && rhs) {
        *this = std::move(rhs);
        return *this;
    }
    T get() { if (m_valid) { return m_value; } }
    bool is_valid() { return m_valid; }
};

template <typename T, typename Callable>
Maybe<T> operator >>= (Maybe<T> m, Callable f) {
    if (!m.is_valid()) {
        return Maybe<T>{};
    }
    else {
        return Maybe<T>(f(m.get()));
    }
}

