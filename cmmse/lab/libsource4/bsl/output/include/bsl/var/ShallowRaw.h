/***************************************************************************
 * 
 * 
 **************************************************************************/
 
 
 
/**
 * @file ShallowRaw.h
 * @brief 
 *  
 **/
#ifndef  __BSL_VAR_SHALLOW_RAW_H__
#define  __BSL_VAR_SHALLOW_RAW_H__
#include "bsl/var/IVar.h"

namespace bsl{
namespace var{
    /**
    * @brief ShallowRaw��һ��raw���ͣ�����ֻά��ָ��ͳ��ȣ���ά�����ݱ���������
    *  
    *  
    */
    class ShallowRaw: public IVar{
    public:
        typedef IVar::string_type           string_type;
        typedef IVar::field_type            field_type;
        typedef IVar::raw_type              raw_type;

        //special methods
        ShallowRaw()
            :_value(){}

        ShallowRaw( const ShallowRaw& other )
            :IVar(other), _value(other._value){ }

        explicit ShallowRaw( const raw_type& value_ )
            :IVar(), _value(value_){}

        ShallowRaw( const void *data_, size_t size_ )
            :IVar(), _value(data_, size_) {}

        virtual ~ShallowRaw(){ } 

        ShallowRaw& operator = ( const ShallowRaw& other ){
            if ( this != &other ){
                _value = other._value;
            }
            return *this;
        }

        //methods for all
        /**
         * @brief ��������
         *
         * @return  void 
         * @retval   
         * @see 
         **/
        virtual void clear(){
            _value.data = NULL;
            _value.length = 0;
        }

        /**
         * @brief ��¡����
         *
         * �ú���ֻ��¡������㣬����¡�ӽ�㣬���������ͣ���¡ָ��Ľ��
         *
         * @param [in] rp   : bsl::ResourcePool&
         * @return  ShallowRaw& 
         * @retval   
         * @see 
        **/
        virtual ShallowRaw& clone( bsl::ResourcePool& rp ) const {
            return rp.clone(*this);
        }

        /**
         * @brief ���������Ϣ�������ڵ��ԣ���ͨ��verbose_level���Ƶݹ����
         *
         * @return  string_type 
         * @retval   
         * @see 
        **/
        virtual string_type dump(size_t verbose_level = 0) const {
            string_type res;
            res.appendf("[bsl::var::ShallowRaw] data[%p] length[%zd]", _value.data, _value.length);
            if ( _value.data != NULL && verbose_level > 0 ){
                res.append(" value[");
                const char * bytes = static_cast<const char*>(_value.data);
                for( size_t i = 0; i < _value.length; ++ i){
                    res.appendf("\\x%02hhx", bytes[i]);
                }
                res.append("]");
            }
            return res;
        }

        /**
         * @brief ת��Ϊ�ַ���
         *
         * @return  string_type 
         * @retval   
         * @see 
        **/
        virtual string_type to_string() const {
            return dump(0);
        }

        /**
         * @brief ��ȡ�����ַ���������var���Ͷ�֧�֣������ڵ���ʹ�ã������������жϣ�
         *
         * @return  string_type 
         * @retval   
         * @see 
        **/
        virtual string_type get_type() const {
            return "bsl::var::ShallowRaw";
        }

        /**
         * @brief ��ȡ�������루����var���Ͷ�֧�֣�
         *
         * @return  IVar::mask_type 
         * @retval   
         * @see 
        **/
        virtual IVar::mask_type get_mask() const {
            return IVar::IS_RAW;
        }

        virtual ShallowRaw& operator = ( IVar& other ){
            if ( this != &other ){
                _value = other.to_raw();
            }
            return *this;
        }

        virtual bool is_raw() const {
            return true;
        }

        //all other is_xxx() return false;

        //methods for raw
        virtual ShallowRaw& operator = ( const raw_type& val ){
            _value = val;
            return *this;
        }

        virtual raw_type to_raw() const {
            return _value;
        }

        using IVar::operator =;
    private:
        raw_type _value;
    };

}}   //namespace bsl::var
#endif  //__BSL_VAR_SHALLOW_RAW_H__

/* vim: set ts=4 sw=4 sts=4 tw=100 */