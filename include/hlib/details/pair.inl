template<class F, class S>
inline pair<F, S>::pair() HLIB_NOEXCEPT
{}

template<class F, class S>
inline pair<F, S>::pair(const pair& other) HLIB_NOEXCEPT
	: first(other.first)
	, second(other.second)
{
}

template<class F, class S>
inline pair<F, S>::pair(pair&& other) HLIB_NOEXCEPT
	: first(static_cast<F&&>(other.first))
	, second(static_cast<S&&>(other.second))
{
}

template<class F, class S>
inline pair<F, S>::pair(const F& key, const S& value) HLIB_NOEXCEPT
	: first(key)
	, second(value)
{
}

template<class F, class S>
inline pair<F, S>::pair(F&& key, S&& value) HLIB_NOEXCEPT
	: first(static_cast<F&&>(key))
	, second(static_cast<S&&>(value))
{
}

template<class F, class S>
inline pair<F, S>& pair<F, S>::operator=(const pair& other) {
	first = other.first;
	second = other.second;
	return *this;
}

template<class F, class S>
inline pair<F, S>& pair<F, S>::operator=(pair&& other) {
	first = static_cast<F&&>(other.first);
	second = static_cast<S&&>(other.second);
	return *this;
}

template<class F, class S>
inline pair<class remove_reference<F>::type, class remove_reference<S>::type> make_pair(F&& f, S&& s)
{
	return pair<class remove_reference<F>::type, class remove_reference<S>::type>(
		  static_cast<F&&>(f)
		, static_cast<S&&>(s)
		);
}
