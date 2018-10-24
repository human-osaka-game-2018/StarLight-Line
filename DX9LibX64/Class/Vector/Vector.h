/**
* @file Vector.h
* @brief �x�N�g�����֌W�����v�Z���s��
* @author Harutaka Tsujino
* @date 15-10-2018
*/

#pragma once
#include <windows.h>	
#include <d3dx9.h>

namespace CalcVector
{
	/**
	* @fn VOID UnitVec2(D3DXVECTOR2* pStraightUnitVec, D3DXVECTOR2 destPt, D3DXVECTOR2 oriPt)
	* @brief ������2�_����P�ʃx�N�g�����쐬����
	* @param (pStraightUnitVec) ���������x�N�g����������
	* @param (destPt) �I�_
	* @param (oriPt) �n�_
	* @return �Ȃ�
	* @detail ������2�_����x�N�g�����쐬�A���̌㐳�K�����s�������ɑ������
	*/
	VOID UnitVec2(D3DXVECTOR2* pStraightUnitVec, D3DXVECTOR2 destPt, D3DXVECTOR2 oriPt);

	/**
	* @fn VOID NormalUnitVec2Y(D3DXVECTOR2* pNormalUnitVec, D3DXVECTOR2 baseVec)
	* @brief baseVec��Y���E����90�x��]�����P�ʃx�N�g���𐶐�����
	* @param (pNormalUnitVec) ���������x�N�g����������
	* @param (baseVec) 90�x��]�������ƂȂ�x�N�g��
	* @return �Ȃ�
	* @detail �����̃x�N�g���𐳋K���A���̌��]�s��𐶐�������
	* ���K�������x�N�g���Ɗ|�����킹���̌��ʂ������ɑ������
	*/
	VOID NormalUnitVec2Y(D3DXVECTOR2* pNormalUnitVec, D3DXVECTOR2 baseVec);

	/**
	* @fn FLOAT Vec2Cross(D3DXVECTOR2 secondVec, D3DXVECTOR2 baseVec)
	* @brief 2�����x�N�g���̊O�όv�Z������
	* @param (secondVec) ���ƂȂ�x�N�g���Ɋ|�����킹��x�N�g��
	* @param (baseVec) �O�ς̊��ƂȂ�x�N�g��
	* @return �O�ς̌v�Z����
	* @detail baseVec�����Ƃ���,2�����x�N�g���̊O�όv�Z������
	*/
	FLOAT Vec2Cross(D3DXVECTOR2 secondVec, D3DXVECTOR2 baseVec);

	/**
	* @fn FLOAT Vec2Rad(D3DXVECTOR2 secondVec, D3DXVECTOR2 baseVec)
	* @brief ������2�����x�N�g������Ȃ�p�x�̌v�Z������
	* @param (secondVec) ���ƂȂ�x�N�g���Ɋ|�����킹��x�N�g��
	* @param (baseVec) �p�x�v�Z�̊��ƂȂ�x�N�g��
	* @return �v�Z���ʂ̊p�x
	* @detail ���ς�p��������2�����x�N�g������Ȃ�p�x���Z�o�A���̌�O�ς�p������������
	*/
	FLOAT Vec2Rad(D3DXVECTOR2 secondVec, D3DXVECTOR2 baseVec);
}
