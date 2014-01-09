#ifndef _CACHE_H_
#define _CACHE_H_

#include <cstdlib>
#include <list>
#include <unordered_map>

template <typename K, typename V>
class Cache {
 public:
  explicit Cache(size_t capacity) : capacity_(capacity) {}

  void Put(const K& k, const V& v);
  bool Get(const K& k, V* v);

 private:
  size_t capacity_;
  std::list<std::pair<K, V>> l_;
  std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> m_;
};

template <typename K, typename V>
void Cache<K, V>::Put(const K& k, const V& v) {
  if (m_.count(k) != 0) {
    l_.erase(m_[k]);
  } else if (m_.size() == capacity_) {
    m_.erase(l_.back().first);
    l_.pop_back();
  }
  l_.push_front(std::make_pair(k, v));
  m_[k] = l_.begin();
}

template <typename K, typename V>
bool Cache<K, V>::Get(const K& k, V* v) {
  if (v == nullptr) return false;
  if (m_.count(k) == 0) return false;
  *v = m_[k]->second;
  l_.erase(m_[k]);
  l_.push_front(std::make_pair(k, *v));
  m_[k] = l_.begin();
  return true;
}

#endif  // _CACHE_H_
