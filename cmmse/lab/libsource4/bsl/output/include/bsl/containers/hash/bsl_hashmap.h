/***************************************************************************
 * 
 * 
 **************************************************************************/
 
 
 
/**
 * @file hashmap.h
 * @brief ʵ�ֹ���key value�Ե�hash����
 * 	�̲߳���ȫ
 *  
 **/


#ifndef  __BSL_HASHMAP_H_
#define  __BSL_HASHMAP_H_

#include <bsl/containers/hash/bsl_hashtable.h>

namespace bsl
{

template <class _Key, /*��Ϊhashkey������*/
		 class _Value,	/*��Ϊhash value������*/
		 /**
		  * hash �����ķº���������
		  * struct xhash {
		  * 	inline size_t operator () (const _Key &_1);
		  * };
		  **/
		 class _HashFun = xhash<_Key>,
		 /**
		  * �ж�����key��ȵķº���
		  * ���� struct equal {
		  * 	inline bool operator () (const _Tp &_1, const _Tp &_2) const ;
		  * };
		  */
		 class _Equl = std::equal_to<_Key>,	
		 /**
		  * �ռ��������Ĭ�ϵĿռ�������ܹ���Ч�ʵĹ���С�ڴ棬��ֹ�ڴ���Ƭ
		  * �����������������ڲ����ͷ�������ڴ�
		  *
		  * bsl_alloc<_Key>���ڴ���������������������������ͷ��ڴ棬
		  * ���ǲ�����Ч��ֹ�ڴ���Ƭ
		  */
		 class _InnerAlloc = bsl_sample_alloc<bsl_alloc<_Key>, 256>
		>
class hashmap
{
	typedef _Key key_type;
	typedef _Value value_type;
	//typedef bsl::pair<_Key, _Value> _Pair;	//��key value�������Ϊ�ײ������Ĵ洢value
	typedef std::pair<_Key, _Value> _Pair;	//��key value�������Ϊ�ײ������Ĵ洢value

	typedef hashmap<_Key, _Value, _HashFun, _Equl, _InnerAlloc> _Self;
	typedef bsl_hashtable<_Key, _Pair, _HashFun, _Equl, pair_first<_Pair>, _InnerAlloc> hash_type;
	hash_type _ht;	//�ײ�hash��
public:
	typedef typename hash_type::iterator iterator;
	typedef typename hash_type::const_iterator const_iterator;

private:
	_Self & operator = (const _Self &) {return *this;}
public:
	/**
	 * @brief ���ص���������ʼ��ַ
	 *
	 * @return  iterator 
	 * @retval   
	 * @see 
	**/
	iterator begin() {
		return _ht.begin(); 
	}
	const_iterator begin() const {
		return _ht.begin();
	}

	/**
	 * @brief ���ص������Ľ�����ַ
	 *
	 * @return  iterator 
	 * @retval   
	 * @see 
	**/
	iterator end() { 
		return _ht.end(); 
	}

	const_iterator end() const {
		return _ht.end();
	}

	/**
	 * @brief ����hash��Ŀǰ�ж��ٸ�Ԫ��
	 *
	 * @return  size_t ��ǰ��Ԫ�ظ���
	 * @retval   
	 * @see 
	**/
	size_t size() const { 
		return _ht.size(); 
	}

	/**
	 * @brief ����һ��hashmap
	 *
	 * @param [in/out] bitems   : int	����hashͰ�Ĵ�С
	 * @param [in/out] hf   : const _HashFun& ����hash����
	 * @param [in/out] eq   : const _Equl&	������ȱȽϺ���
	 * @return  int ����	0		��ʾ�����ɹ�
	 * 				����	����	��ʾ����ʧ��
	 * @retval   
	 * @see 
	**/
	int create(size_t bitems, const _HashFun &hf = _HashFun(), const _Equl & eq = _Equl()) {
		if (_ht.create(bitems, hf, eq) != 0) {
			return -1;
		}
		return 0;
	}

	/**
	 * @brief ����hash��
	 *
	 * @return  int ����0��ʾɾ���ɹ���������ʾɾ��ʧ��
	 * @retval   
	 * @see 
	**/
	int destroy() {
		return _ht.destroy();
	}

	/**
	 * @brief ����ָ��key��ȡvalueֵ
	 *
	 * @param [in/out] k   : const key_type&	ָ���Ĳ���key
	 * @param [in/out] val   : value_type*	��ȡ��valueֵ�Ĵ洢��ַ
	 * 				���value��Ϊ�գ���*val��ֵ���ҵ�ֵ
	 * @return  int 
	 *				���� HASH_EXIST		��ʾhashֵ����
	 *				���� HASH_NOEXIST	��ʾhashֵ������
	 * @retval   
	 * @see 
	**/
	int get(const key_type &k, value_type *val=0) const {
		_Pair *ptr = _ht.find(_ht._hashfun(k), k);
		if (ptr == NULL) {
			return HASH_NOEXIST;
		}
		if (val) {
			*val = ptr->second;
		}
		return HASH_EXIST;
	}
	int get(const key_type &k, value_type *val=0) {
		_Pair *ptr = _ht.find(_ht._hashfun(k), k);
		if (ptr == NULL) {
			return HASH_NOEXIST;
		}
		if (val) {
			*val = ptr->second;
		}
		return HASH_EXIST;
	}

	/**
	 * @brief ����ָ����key��ȡvalueָ��
	 *
	 * @param [in/out] k   : const key_type&
	 * @return  _Pair*  �����ڷ���NULL
	 * @retval   
	 * @see 
	 * @note 
	**/
	_Pair * find (const key_type &k) const {
		return _ht.find(_ht._hashfun(k), k);
	}
	_Pair * find (const key_type &k) {
		return _ht.find(_ht._hashfun(k), k);
	}

	/**
	 * @brief ��key �� value �� ���� hash����
	 *
	 * @param [in/out] k   : const key_type&	keyֵ	
	 * @param [in/out] val   : const value_type&	valueֵ
	 * @param [in/out] flag   : int	
	 * 				flag ����0�����ֵ����ֱ�ӷ��أ�
	 * 				��0��ʾ�����ֵ���ڣ��滻��ֵ
	 * @return  int 	
	 *  			����	-1	��ʾset���ó���, (�޷������½��)
	 * 			��������ʾ����ɹ�������ɹ�����������״̬
	 * 				����	HASH_OVERWRITE	��ʾ���Ǿɽ��ɹ�(��flag��0��ʱ�򷵻�)
	 * 				����	HASH_INSERT_SEC	��ʾ�����½��ɹ�
	 * 				����	HASH_EXIST	��ʾhash��������(��flagΪ0��ʱ�򷵻�)
	 * @retval   
	 * @see 
	**/
	int set(const key_type &k, const value_type &val, int flag = 0) {
		return _ht.set_map(_ht._hashfun(k), k, val, flag);
	}

	/**
	 * @brief ����ָ����keyɾ�����
	 *
	 * @param [in/out] k   : const key_type&
	 * @return  int 
	 * 		����	HASH_EXIST��ʾ�����ڲ�ɾ���ɹ�
	 * 		����	HASH_NOEXIST��ʾ��㲻���ڲ���ɾ��
	 * @retval   
	 * @see 
	**/
	int erase(const key_type &k) {
		return _ht.erase(_ht._hashfun(k), k);
	}

	/**
	 * @brief ������������hash�����и�ֵ
	 *
	 * @param [in/out] __begin   : _Iterator	����������ʼ��ַ
	 * @param [in/out] __end   : _Iterator		�������Ľ�����ַ
	 * @return int 	0	��ʾ��ֵ�ɹ���������ʾʧ��
	 * @retval   
	 * @see 
	**/
	template <class _Iterator>
	int assign(_Iterator __begin, _Iterator __end) {
		return _ht.assign(__begin, __end);
	}

	template <class _Archive>
	int serialization(_Archive &ar) {
		return bsl::serialization(ar, _ht);
	}

	template <class _Archive>
	int deserialization(_Archive &ar) {
		return bsl::deserialization(ar, _ht);
	}

	int clear() {
		return _ht.clear();
	}
};

};

#endif  //__HASHMAP_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */