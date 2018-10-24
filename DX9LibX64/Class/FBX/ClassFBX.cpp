include<windows.h>
#include <fbxsdk.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "ClassDirectX.h"
#include "ClassFBX.h"

#pragma comment(lib,"libfbxsdk-md.lib")

using namespace fbxsdk;

VOID FBX::GetTextureName(FbxSurfaceMaterial* pMaterial, const char* pMatAttr, FBXModel* pFBXModel)
{
	//	�v���p�e�B���擾
	fbxsdk::FbxProperty prop = pMaterial->FindProperty(pMatAttr);

	//	FbxLayerTexture �̐����擾
	int layeredTextureCount = prop.GetSrcObjectCount<fbxsdk::FbxLayeredTexture>();

	//	�A�^�b�`���ꂽ�e�N�X�`����FbxLayeredTexture �̏ꍇ
	if (0 < layeredTextureCount)
	{
		//	�A�^�b�`���ꂽ�e�N�X�`���̐������J��Ԃ�
		for (int i = 0; layeredTextureCount > i; i++)
		{
			//	�e�N�X�`�����擾
			fbxsdk::FbxLayeredTexture* pLayeredTexture = prop.GetSrcObject<fbxsdk::FbxLayeredTexture>(i);

			//	���C���[�����擾
			int textureCount = pLayeredTexture->GetSrcObjectCount<fbxsdk::FbxFileTexture>();

			//	���C���[�������J��Ԃ�
			for (int j = 0; textureCount > j; j++)
			{
				//	�e�N�X�`�����擾
				fbxsdk::FbxFileTexture* pFbxFileTexture = prop.GetSrcObject<fbxsdk::FbxFileTexture>(j);

				if (pFbxFileTexture)
				{
					//	�e�N�X�`�������擾
					//	std::string textureName = texture->GetName();
					LPCSTR textureName = pFbxFileTexture->GetRelativeFileName();

					//	UVSet�����擾
					std::string UVSetName = pFbxFileTexture->UVSet.Get().Buffer();

					//	UVSet�����r���Ή����Ă���e�N�X�`���Ȃ�ێ����ăf�[�^�N���X��UV���W�������
					if (pFBXModel->m_uvSet.uvSetName == UVSetName)
					{
						pFBXModel->m_pTmpTexture = new TextureData;
						pFBXModel->m_pTmpTexture->m_TextureName = textureName;
						pFBXModel->m_pTextureData.push_back(pFBXModel->m_pTmpTexture);

						if (FAILED(D3DXCreateTextureFromFile(
							DirectX::m_directXInstances.m_pDirectX3DDevice,
							pFBXModel->m_pTextureData[pFBXModel->m_fileTextureCount]->m_TextureName,
							&pFBXModel->m_pTextureData[pFBXModel->m_fileTextureCount]->m_pTexture)))
						{
							pFBXModel->m_pTextureData[pFBXModel->m_fileTextureCount]->m_pTexture = NULL;
						}
						pFBXModel->m_fileTextureCount++;
					}
				}
			}
		}
	}

	else
	{
		//	�e�N�X�`�������擾
		int fileTextureCount = prop.GetSrcObjectCount<fbxsdk::FbxFileTexture>();

		if (0 < fileTextureCount)
		{
			//	�e�N�X�`���̐������J��Ԃ�
			for (int i = 0; fileTextureCount > i; i++)
			{
				//	�e�N�X�`�����擾
				fbxsdk::FbxFileTexture* pFbxFileTexture = prop.GetSrcObject<fbxsdk::FbxFileTexture>(i);

				if (pFbxFileTexture)
				{
					//	�e�N�X�`�������擾
					//	std::string textureName = texture->GetName();
					LPCSTR textureName = pFbxFileTexture->GetRelativeFileName();

					//	UVSet�����擾
					std::string UVSetName = pFbxFileTexture->UVSet.Get().Buffer();

					//	UVSet�����r���Ή����Ă���e�N�X�`���Ȃ�ێ�
					if (pFBXModel->m_uvSet.uvSetName == UVSetName)
					{
						pFBXModel->m_pTmpTexture = new TextureData;
						pFBXModel->m_pTmpTexture->m_TextureName = textureName;
						pFBXModel->m_pTextureData.push_back(pFBXModel->m_pTmpTexture);

						if (FAILED(D3DXCreateTextureFromFile(
							DirectX::m_directXInstances.m_pDirectX3DDevice,
							pFBXModel->m_pTextureData[pFBXModel->m_fileTextureCount]->m_TextureName,
							&pFBXModel->m_pTextureData[pFBXModel->m_fileTextureCount]->m_pTexture)))
						{
							pFBXModel->m_pTextureData[pFBXModel->m_fileTextureCount]->m_pTexture = NULL;
						}
						pFBXModel->m_fileTextureCount++;
					}
				}
			}
		}
	}

	return;
}

VOID FBX::GetMaterialData(FbxMesh* pFbxMesh, FBXModel* pFBXModel)
{
	//	���b�V������m�[�h���擾
	fbxsdk::FbxNode* pNode = pFbxMesh->GetNode();

	//	�}�e���A���̐����擾
	pFBXModel->m_materialCount = pNode->GetMaterialCount();

	//	�e�N�X�`�@�̐����J�E���g����
	static int fileTextureCount = 0;

	//	�}�e���A���̐������J��Ԃ�
	for (int i = 0; i < pFBXModel->m_materialCount; ++i)
	{
		//	�}�e���A�����擾
		fbxsdk::FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		D3DMATERIAL9 MaterialData;

		if (pMaterial->GetClassId().Is(fbxsdk::FbxSurfaceLambert::ClassId))
		{
			// Lambert�Ƀ_�E���L���X�g
			fbxsdk::FbxSurfaceLambert* lambert = (fbxsdk::FbxSurfaceLambert*)pMaterial;

			// �A���r�G���g
			MaterialData.Ambient.r = (float)lambert->Ambient.Get().mData[0] * (float)lambert->AmbientFactor.Get();
			MaterialData.Ambient.g = (float)lambert->Ambient.Get().mData[1] * (float)lambert->AmbientFactor.Get();
			MaterialData.Ambient.b = (float)lambert->Ambient.Get().mData[2] * (float)lambert->AmbientFactor.Get();
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sAmbient, pFBXModel);

			// �f�B�t���[�Y
			MaterialData.Diffuse.r = (float)lambert->Diffuse.Get().mData[0] * (float)lambert->DiffuseFactor.Get();
			MaterialData.Diffuse.g = (float)lambert->Diffuse.Get().mData[1] * (float)lambert->DiffuseFactor.Get();
			MaterialData.Diffuse.b = (float)lambert->Diffuse.Get().mData[2] * (float)lambert->DiffuseFactor.Get();
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sDiffuse, pFBXModel);

			// �G�~�b�V�u
			MaterialData.Emissive.r = (float)lambert->Emissive.Get().mData[0] * (float)lambert->EmissiveFactor.Get();
			MaterialData.Emissive.g = (float)lambert->Emissive.Get().mData[1] * (float)lambert->EmissiveFactor.Get();
			MaterialData.Emissive.b = (float)lambert->Emissive.Get().mData[2] * (float)lambert->EmissiveFactor.Get();
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sEmissive, pFBXModel);

			// ���ߓx
			MaterialData.Ambient.a = 0.f;
			MaterialData.Diffuse.a = 1.f;
			MaterialData.Emissive.a = 0.f;
			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sTransparentColor, pFBXModel);


			GetTextureName(lambert, fbxsdk::FbxSurfaceMaterial::sNormalMap, pFBXModel);


			pFBXModel->m_materialData.push_back(MaterialData);
		}

		else
		{
			if (pMaterial->GetClassId().Is(fbxsdk::FbxSurfacePhong::ClassId))
			{
				// Phong�Ƀ_�E���L���X�g
				fbxsdk::FbxSurfacePhong* phong = (fbxsdk::FbxSurfacePhong*)pMaterial;

				// �A���r�G���g
				MaterialData.Ambient.r = (float)phong->Ambient.Get().mData[0] * (float)phong->AmbientFactor.Get();
				MaterialData.Ambient.g = (float)phong->Ambient.Get().mData[1] * (float)phong->AmbientFactor.Get();
				MaterialData.Ambient.b = (float)phong->Ambient.Get().mData[2] * (float)phong->AmbientFactor.Get();
				GetTextureName(phong, fbxsdk::FbxSurfaceMaterial::sAmbient, pFBXModel);

				// �f�B�t���[�Y
				MaterialData.Diffuse.r = (float)phong->Diffuse.Get().mData[0] * (float)phong->DiffuseFactor.Get();
				MaterialData.Diffuse.g = (float)phong->Diffuse.Get().mData[1] * (float)phong->DiffuseFactor.Get();
				MaterialData.Diffuse.b = (float)phong->Diffuse.Get().mData[2] * (float)phong->DiffuseFactor.Get();
				GetTextureName(phong, fbxsdk::FbxSurfaceMaterial::sDiffuse, pFBXModel);

				// �G�~�b�V�u
				MaterialData.Emissive.r = (float)phong->Emissive.Get().mData[0] * (float)phong->EmissiveFactor.Get();
				MaterialData.Emissive.g = (float)phong->Emissive.Get().mData[1] * (float)phong->EmissiveFactor.Get();
				MaterialData.Emissive.b = (float)phong->Emissive.Get().mData[2] * (float)phong->EmissiveFactor.Get();
				GetTextureName(phong, fbxsdk::FbxSurfaceMaterial::sEmissive, pFBXModel);

				// ���ߓx
				MaterialData.Ambient.a = 0.f;
				MaterialData.Diffuse.a = 1.f;
				MaterialData.Emissive.a = 0.f;
				MaterialData.Specular.a = 0.f;
				GetTextureName(phong, fbxsdk::FbxSurfaceMaterial::sTransparentColor, pFBXModel);

				// �X�y�L����
				MaterialData.Specular.r = (float)phong->Specular.Get().mData[0] * (float)phong->SpecularFactor.Get();
				MaterialData.Specular.g = (float)phong->Specular.Get().mData[1] * (float)phong->SpecularFactor.Get();
				MaterialData.Specular.b = (float)phong->Specular.Get().mData[2] * (float)phong->SpecularFactor.Get();
				GetTextureName(phong, fbxsdk::FbxSurfaceMaterial::sSpecular, pFBXModel);

				// ����
				//			shininess_ = (float)phong->GetShininess().Get();		??????????????

				// ����
				//			reflectivity_ = (float)phong->GetReflectionFactor().Get();		??????????????

				MaterialData.Power = (float)phong->Shininess.Get();

				GetTextureName(phong, fbxsdk::FbxSurfaceMaterial::sNormalMap, pFBXModel);

				MaterialData.Power = (float)phong->Shininess.Get();

				pFBXModel->m_materialData.push_back(MaterialData);
			}
		}
	}

	return;
}

VOID FBX::GetVertexNormal(FbxMesh* pFbxMesh, FBXModel* pFBXModel)
{
	//--- �@���Z�b�g�����擾 ---//
	INT normalLayerCount = pFbxMesh->GetElementNormalCount();

	//--- ���C���[��������� ---//
	for (INT normalLayer = 0; normalLayer < normalLayerCount; ++normalLayer)
	{
		//--- �@���Z�b�g���擾 ---//
		FbxGeometryElementNormal* normal = pFbxMesh->GetElementNormal(normalLayer);

		//--- �}�b�s���O���[�h�̎擾
		FbxGeometryElement::EMappingMode mapping = normal->GetMappingMode();

		//--- ���t�@�����X���[�h�̎擾 ---//
		FbxGeometryElement::EReferenceMode reference = normal->GetReferenceMode();

		//--- �}�b�s���O���[�h�̔��� ---//
		switch (mapping)
		{
		case FbxGeometryElement::eByControlPoint:

			//--- ���t�@�����X���[�h�̔��� ---//
			switch (reference)
			{
			case FbxGeometryElement::eDirect:
			{
				//--- �@�������擾 ---//
				INT normalCount = normal->GetDirectArray().GetCount();

				//-----------------------------------------------------------------------
				// eDirect �̏ꍇ�f�[�^�͏��ԂɊi�[����Ă���̂ł��̂܂ܕێ�
				//-----------------------------------------------------------------------

				Vertex*& rPVertexBuffer = pFBXModel->m_pVertexBuffer;

				for (INT normalVect = 0; normalVect < normalCount; ++normalVect)
				{
					//--- �@���̎擾 ---//
					rPVertexBuffer[normalVect].m_xNormal = (float)normal->GetDirectArray().GetAt(normalVect)[0];
					rPVertexBuffer[normalVect].m_yNormal = (float)normal->GetDirectArray().GetAt(normalVect)[1];
					rPVertexBuffer[normalVect].m_zNormal = (float)normal->GetDirectArray().GetAt(normalVect)[2];
				}

				break;
			}

			break;

			case FbxGeometryElement::eIndexToDirect:

				break;

			default:

				break;
			}

			break;

		case FbxGeometryElement::eByPolygonVertex:

			//--- ���t�@�����X���[�h�̔��� ---//
			switch (reference)
			{
			case FbxGeometryElement::eDirect:
			{
				//--- �@�������擾 ---//
				INT normalCount = normal->GetDirectArray().GetCount();

				//-----------------------------------------------------------------------
				// eDirect �̏ꍇ�f�[�^�͏��ԂɊi�[����Ă���̂ł��̂܂ܕێ�
				//-----------------------------------------------------------------------

				Vertex*& rPVertexBuffer = pFBXModel->m_pVertexBuffer;

				for (INT normalVect = 0; normalVect < normalCount; ++normalVect)
				{
					//--- �@���̎擾 ---//
					rPVertexBuffer[normalVect].m_xNormal = (float)normal->GetDirectArray().GetAt(normalVect)[0];
					rPVertexBuffer[normalVect].m_yNormal = (float)normal->GetDirectArray().GetAt(normalVect)[1];
					rPVertexBuffer[normalVect].m_zNormal = (float)normal->GetDirectArray().GetAt(normalVect)[2];
				}

				break;
			}

			break;

			case FbxGeometryElement::eIndexToDirect:

				break;

			default:

				break;
			}

			break;

		default:

			break;
		}
	}

	return;
}

//VOID FBX::GetTextureNames(FbxMesh* pFbxMesh, FBXModel* pFBXModel)
//{
//	//--- ���b�V������m�[�h���擾 ---//
//	FbxNode* node = pFbxMesh->GetNode();
//
//	//--- �}�e���A���̐����擾 ---//
//	INT materialCount = node->GetMaterialCount();
//
//	//--- �}�e���A���̐������J��Ԃ� ---//
//	for (INT materialNum = 0; materialNum < materialCount; ++materialNum)
//	{
//		//--- �}�e���A�����擾 ---//
//		FbxSurfaceMaterial* material = node->GetMaterial(materialNum);
//
//		FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
//
//		//--- FbxLayeredTexture �̐����擾 ---//
//		INT layeredTextureCount = prop.GetSrcObjectCount();
//
//		//--- �A�^�b�`���ꂽ�e�N�X�`���� FbxLayeredTexture �̏ꍇ ---//
//		if (0 < layeredTextureCount)
//		{
//			//--- �A�^�b�`���ꂽ�e�N�X�`���̐������J��Ԃ� ---//
//			for (INT j = 0; layeredTextureCount > j; j++)
//			{
//				//--- �e�N�X�`�����擾 ---//
//				FbxLayeredTexture* pLayeredTexture = prop.GetSrcObject<FbxLayeredTexture>(j);
//
//				//--- ���C���[�����擾 ---//
//				INT textureCount = pLayeredTexture->GetSrcObjectCount<FbxFileTexture>();
//
//				//--- ���C���[�������J��Ԃ� ---//
//				for (INT k = 0; textureCount > k; k++)
//				{
//					//--- �e�N�X�`�����擾 ---//
//					FbxFileTexture* m_pTexture = prop.GetSrcObject<FbxFileTexture>(k);
//
//					if (!m_pTexture)
//					{
//						continue;
//					}
//
//					//--- �e�N�X�`�������擾 ---//
//					//std::string textureName = m_pTexture->GetName();
//					std::string textureName = m_pTexture->GetRelativeFileName();
//
//					//--- UVSet�����擾 ---//
//					std::string UVSetName = m_pTexture->UVSet.Get().Buffer();
//
//					//--- UVSet�����r���Ή����Ă���e�N�X�`���Ȃ�ێ� ---//
//					if (pFBXModel->m_uvSet.uvSetName == UVSetName)
//					{
//						pFBXModel->m_uvSet.textures.push_back(textureName);
//					}
//				}
//			}
//		}
//
//		if (0 >= layeredTextureCount)
//		{
//			//--- �e�N�X�`�������擾 ---//
//			INT fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();
//
//			if (0 <= fileTextureCount)
//			{
//				break;
//			}
//
//			//--- �e�N�X�`���̐������J��Ԃ� ---//
//			for (INT j = 0; fileTextureCount > j; j++)
//			{
//				//--- �e�N�X�`�����擾 ---//
//				FbxFileTexture* m_pTexture = prop.GetSrcObject<FbxFileTexture>(j);
//
//				if (m_pTexture)
//				{
//					continue;
//				}
//
//				//--- �e�N�X�`�������擾 ---//
//				//std::string textureName = m_pTexture->GetName();
//				std::string textureName = m_pTexture->GetRelativeFileName();
//
//				//--- UVSet�����擾 ---//
//				std::string UVSetName = m_pTexture->UVSet.Get().Buffer();
//
//				//--- UVSet�����r���Ή����Ă���e�N�X�`���Ȃ�ێ� ---//
//				if (pFBXModel->m_uvSet.uvSetName == UVSetName)
//				{
//					pFBXModel->m_uvSet.textures.push_back(textureName);
//				}
//			}
//		}
//	}
//
//	return;
//}

VOID FBX::GetVertexUV(FbxMesh* pFbxMesh, FBXModel* pFBXModel)
{
	//--- UV�Z�b�g�����擾 ---//
	INT UVLayerCount = pFbxMesh->GetElementUVCount();

	for (INT uvLayer = 0; uvLayer < UVLayerCount; ++uvLayer)
	{
		//--- UV�o�b�t�@���擾 ---//
		FbxGeometryElementUV* UV = pFbxMesh->GetElementUV(uvLayer);

		//--- �}�b�s���O���[�h�̎擾
		FbxGeometryElement::EMappingMode mapping = UV->GetMappingMode();

		//--- ���t�@�����X���[�h�̎擾 ---//
		FbxGeometryElement::EReferenceMode reference = UV->GetReferenceMode();

		//--- UV�����擾 ---//
		INT uvCount = UV->GetDirectArray().GetCount();

		//--- �}�b�s���O���[�h�̔��� ---//
		switch (mapping)
		{
		case FbxGeometryElement::eByControlPoint:

			break;

		case FbxGeometryElement::eByPolygonVertex:

			//--- ���t�@�����X���[�h�̔��� ---//
			switch (reference)
			{
			case FbxGeometryElement::eDirect:

				break;

			case FbxGeometryElement::eIndexToDirect:
			{
				FbxLayerElementArrayTemplate<INT>* uvIndex = &UV->GetIndexArray();
				INT uvIndexCount = uvIndex->GetCount();

				//--- UV��ێ� ---// 
				Point2 temp;

				UvSet& uvSet = pFBXModel->m_uvSet;

				for (INT index = 0; index < uvIndexCount; ++index)
				{
					temp.x = (float)UV->GetDirectArray().GetAt(uvIndex->GetAt(index))[0];

					temp.y = 1.0f - (float)UV->GetDirectArray().GetAt(uvIndex->GetAt(index))[1];

					uvSet.uvBuffer.push_back(temp);
				}

				//--- UVSet�����擾 ---//
				uvSet.uvSetName = UV->GetName();
			}

			break;

			default:

				break;
			}

			break;

		case FbxGeometryElement::eByEdge:

			break;

		case FbxGeometryElement::eByPolygon:

			break;

		default:

			break;
		}
	}

	return;
}

VOID FBX::GetShape(FbxMesh* pFbxMesh, FBXModel* pFBXModel)
{
	//--- �|���S�������擾 ---//
	INT polygonCount = pFBXModel->m_polygonCount = pFbxMesh->GetPolygonCount();

	//--- �����_�����擾 ---//
	INT vertexCount = pFBXModel->m_vertexCount = pFbxMesh->GetControlPointsCount();

	//--- �C���f�b�N�X�����擾 ---//
	INT indexCount = pFBXModel->m_indexCount = pFbxMesh->GetPolygonVertexCount();

	//--- ���_�o�b�t�@�̎擾 ---//
	FbxVector4* vertices = pFbxMesh->GetControlPoints();

	//--- �C���f�b�N�X�o�b�t�@�̎擾 ---//
	INT* indices = pFbxMesh->GetPolygonVertices();

	//--- �|���S���T�C�Y���擾 ---//
	INT*& rPPolygonSize = pFBXModel->m_pPolygonSize = new INT[polygonCount];

	for (INT polygon = 0; polygon < polygonCount; ++polygon)
	{
		rPPolygonSize[polygon] = pFbxMesh->GetPolygonSize(polygon);
	}

	//--- ���_���W�̃L���X�g�ƃn�[�h�R�s�[ ---//
	Vertex*& rPVertexBuffer = pFBXModel->m_pVertexBuffer = new Vertex[pFBXModel->m_indexCount];

	for (INT vertex = 0; vertex < vertexCount; ++vertex)
	{
		//--- vertex�Ԗڂ̒��_�̕W�w���擾 ---//
		rPVertexBuffer[vertex].m_x = (float)vertices[vertex][0];

		//--- vertex�Ԗڂ̒��_�̍��W�x���擾 ---//
		rPVertexBuffer[vertex].m_y = (float)vertices[vertex][1];

		//--- vertex�Ԗڂ̒��_�̍��W�y���擾 ---//
		rPVertexBuffer[vertex].m_z = (float)vertices[vertex][2];
	}

	//--- �C���f�b�N�X�o�b�t�@�̃n�[�h�R�s�[ ---//
	INT*& rPIndexBuffer = pFBXModel->m_pIndexBuffer = new INT[indexCount];

	for (INT index = 0; index < indexCount; ++index)
	{
		rPIndexBuffer[index] = indices[index];
	}

	return;
}

VOID FBX::GetMesh(FbxNode* pChildNode, FBXModel* pFBXModel)
{
	FbxNodeAttribute* nodeAttribute = pChildNode->GetNodeAttribute();

	if (nodeAttribute)
	{
		//--- ���b�V���m�[�h���� ---//
		if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			FbxMesh* pFbxMesh = pChildNode->GetMesh();

			GetShape(pFbxMesh, pFBXModel);

			//--- ���_�̖@�����W���擾 ---//
			GetVertexNormal(pFbxMesh, pFBXModel);

			GetVertexUV(pFbxMesh, pFBXModel);

			GetMaterialData(pFbxMesh, pFBXModel);
		}
	}

	INT childNodes = pChildNode->GetChildCount();

	for (INT nodes = 0; nodes < childNodes; ++nodes)
	{
		GetMesh(pChildNode->GetChild(nodes), pFBXModel);
	}

	return;
}

FBXModel g_fBXModel;

BOOL FBX::Initialize()
{
	FbxManager* pFbxManager = FbxManager::Create();

	FbxImporter* pFbxImporter = FbxImporter::Create(pFbxManager, "");

	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "");

	pFbxImporter->Initialize("Handgun_fbx_6.1_ASCII.fbx");

	pFbxImporter->Import(pFbxScene);

	FbxNode* pRootNode = pFbxScene->GetRootNode();

	if (pRootNode)
	{
		INT childNodes = pRootNode->GetChildCount();

		for (INT nodes = 0; nodes < childNodes; ++nodes)
		{
			GetMesh(pRootNode->GetChild(nodes), &g_fBXModel);
		}
	}

	//importer->Destroy();

	return TRUE;
}

VOID FBX::DrawFBX(FBXModel* pFBXModel)
{
#define MY_FVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2)

	CustomVertex cusV4Background[4] =
	{
		{ -1.f,   0 - 1.f, 0.f,1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ 1280 - 1.f,   0 - 1.f, 0.f,1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ 1280 - 1.f, 720 - 1.f, 0.f,1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ -1.f, 720 - 1.f, 0.f,1.f, 0xFFFFFFFF, 0.f, 1.f }
	};

	LPDIRECT3DDEVICE9& rDirectX3DDevice = DirectX::m_directXInstances.m_pDirectX3DDevice;

	rDirectX3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	rDirectX3DDevice->SetTexture(0, NULL);
	rDirectX3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, cusV4Background, sizeof(CustomVertex));

	DirectX::m_directXInstances.m_pDirectX3DDevice->SetFVF(MY_FVF);

	for (int i = 0; i < pFBXModel->m_materialCount; i++)
	{
		rDirectX3DDevice->SetMaterial(&pFBXModel->m_materialData[i]);
	}

	for (unsigned int n = 0; n < pFBXModel->m_pTextureData.size(); n++)
	{
		rDirectX3DDevice->SetTexture(n, pFBXModel->m_pTextureData[n]->m_pTexture);
	}

	Camera camera;

	camera.SetTransform();

	D3DXMATRIX			m_MatWorld;
	D3DXMatrixIdentity(&m_MatWorld);

	// ��]
	D3DXMATRIX			matHeading;
	D3DXMatrixRotationY(&matHeading, 0);
	D3DXMatrixMultiply(&m_MatWorld, &m_MatWorld, &matHeading);

	// �ړ�
	D3DXMATRIX			matPosition;	// �ʒu���W�s��
	D3DXMatrixTranslation(&matPosition, 0, 0, 0);
	D3DXMatrixMultiply(&m_MatWorld, &m_MatWorld, &matPosition);
	rDirectX3DDevice->SetTransform(D3DTS_WORLD, &m_MatWorld);

	D3DXVECTOR3 vecDirection(0, 0, 1);
	D3DLIGHT9 light;

	ZeroMemory(&light, sizeof(D3DLIGHT9));
	
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.f;
	light.Diffuse.g = 1.f;
	light.Diffuse.b = 1.f;

	light.Specular.r = 1.f;
	light.Specular.b = 1.f;
	light.Specular.g = 1.f;

	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);

	light.Range = 200.f;
	rDirectX3DDevice->SetLight(0, &light);
	rDirectX3DDevice->LightEnable(0, TRUE);

	rDirectX3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		pFBXModel->m_polygonCount,
		pFBXModel->m_pVertexBuffer,
		sizeof(Vertex));
}
