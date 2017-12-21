#if !(defined MPL_UTILITY_HPP)

#define MPL_UTILITY_HPP

#include <iterator>
#include <limits>
#include <type_traits>
		
namespace mpl {

  namespace detail {

    template<typename T>
    struct iterator_traits : public std::iterator_traits<T> {
      typedef typename std::iterator_traits<T>::value_type insert_type;
    };

    template<typename T>
    struct iterator_traits<std::back_insert_iterator<T>> : public std::iterator_traits<std::back_insert_iterator<T>> {
      typedef typename T::value_type insert_type;
    };

    template<typename from_type, typename to_type>
    struct is_narrowing {
      static constexpr bool value=std::numeric_limits<from_type>::max()>std::numeric_limits<to_type>::max();
    };
    
    template<typename T, bool is_enum=std::is_enum<T>::value>
    struct underlying_type;

    template<typename T>
    struct underlying_type<T, true> {
      typedef typename std::underlying_type<T>::type type;
      static constexpr auto value(const T &v) {
	return static_cast<int>(v);
      }
    };

    template<typename T>
    struct underlying_type<T, false> {
      typedef T type;
      static constexpr auto value(const T &v) {
	return static_cast<int>(v);
      }
    };
    
    template<typename T>
    struct is_valid_tag {
      static constexpr bool value=
	(std::is_integral<T>::value or std::is_enum<T>::value) and
	(not is_narrowing<typename underlying_type<T>::type, int>::value);
    };
    
  }

}

#endif
