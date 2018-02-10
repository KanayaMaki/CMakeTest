//
//	content	:	������n�̃N���X��֐�
//	author	:	SaitoYoshiki
//

#pragma once


#include "./Pot/Atom/defines.h"
#include "./Pot/Atom/typedef.h"

#include "./Pot/Atom/function.h"
#include "./Pot/Atom/hashString.h"


namespace cpot {


//�^�𒲂ׂ�
#pragma region Type

using Type = HashString<28>;

//���N���X�Ő錾����
#pragma region Base

#define CPOT_TYPE_BASE(THIS)									\
public:															\
	static const Type& SGetTypeName() {							\
		static Type t(CPOT_NAME_EXTEND(THIS));					\
		return t;												\
	}															\
	virtual BOOL CanCast(const Type& aTypeName) const {			\
		return THIS::SEqualType(aTypeName);						\
	}															\
	virtual BOOL EqualType(const Type& aTypeName) const {		\
		return THIS::SEqualType(aTypeName);						\
	}															\
	virtual const Type& GetTypeName() const {					\
		return SGetTypeName();									\
	}															\
																\
protected:														\
	static BOOL SEqualType(const Type& aTypeName) {				\
		return	SGetTypeName() == aTypeName;					\
	}															\
private:

#pragma endregion


//�h���N���X�Ő錾����
#pragma region Extend


#define CPOT_TYPE(THIS, SUPER)									\
	using Super = SUPER;										\
public:															\
	static const Type& SGetTypeName() {							\
		static Type t(CPOT_NAME_EXTEND(THIS));					\
		return t;												\
	}															\
	BOOL CanCast(const Type& aTypeName) const override {		\
		if (THIS::SEqualType(aTypeName)) return true;			\
		return SUPER::SEqualType(aTypeName);					\
	}															\
	BOOL EqualType(const Type& aTypeName) const override {		\
		return THIS::SEqualType(aTypeName);						\
	}															\
	const Type& GetTypeName() const override {					\
		return SGetTypeName();									\
	}															\
																\
protected:														\
	static BOOL SEqualType(const Type& aTypeName) {				\
		return	SGetTypeName() == aTypeName;					\
	}															\
private:

#pragma endregion


//���d�p�����Ă���N���X�Ő錾����
#pragma region Double


#define CPOT_TYPE_DOUBLE(THIS, SUPER1, SUPER2)					\
	using Super1 = SUPER1;										\
	using Super2 = SUPER2;										\
public:															\
	static const Type& SGetTypeName() {							\
		static Type t(CPOT_NAME_EXTEND(THIS));					\
		return t;												\
	}															\
	BOOL CanCast(const Type& aTypeName) const override {		\
		if (THIS::SEqualType(aTypeName)) return true;			\
		if (SUPER1::SEqualType(aTypeName)) return true;			\
		return SUPER2::SEqualType(aTypeName);					\
	}															\
	BOOL EqualType(const Type& aTypeName) const override {		\
		return THIS::SEqualType(aTypeName);						\
	}															\
	const Type& GetTypeName() const override {					\
		return SGetTypeName();									\
	}															\
																\
protected:														\
	static BOOL SEqualType(const Type& aTypeName) {				\
		return	SGetTypeName() == aTypeName;					\
	}															\
private:

#pragma endregion

#pragma endregion

}