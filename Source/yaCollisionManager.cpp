#include "yaCollisionManager.h"
#include "yaScene.h"
#include "yaSceneManager.h"

namespace ya
{
	std::bitset<(UINT)eLayerType::End> CollisionManager::mLayerCollisionMatrix[(UINT)eLayerType::End] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap;

	void CollisionManager::Initialize()
	{
	}
	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetPlayScene();
		for (UINT row = 0; row < (UINT)eLayerType::End; row++)
		{
			for (UINT column = 0; column < (UINT)eLayerType::End; column++)
			{
				if (mLayerCollisionMatrix[row][column])
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)column);
				}
			}
		}
	}
	void CollisionManager::FixedUpdate()
	{
	}
	void CollisionManager::Render()
	{
	}
	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = 0;
		int column = 0;

		if ((UINT)left <= (UINT)right)
		{
			row = (UINT)left;
			column = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			column = (UINT)left;
		}

		mLayerCollisionMatrix[row][column] = enable;
	}
	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetGameObjects(left);
		const std::vector<GameObject*>& rights = scene->GetGameObjects(right);

		if (left == right)
		{
			for (UINT i =0; i<lefts.size(); i++)
			{
				GameObject* lObj = lefts[i];
				if (lObj->GetState() != GameObject::Active)
					continue;
				if (lObj->GetComponent<Collider2D>() == nullptr)
					continue;


				for (UINT k = i; k < lefts.size(); k++)
				{
					GameObject* rObj = lefts[k];
					if (rObj->GetState() != GameObject::Active)
						continue;
					if (rObj->GetComponent<Collider2D>() == nullptr)
						continue;
					if (lObj == rObj)
						continue;
					std::vector<Collider2D*>lCols = lObj->GetComponents<Collider2D>();
					std::vector<Collider2D*>rCols = rObj->GetComponents<Collider2D>();
					for (UINT l = 0;  l < lCols.size();  l++)
					{
						for (UINT r = 0; r < rCols.size(); r++)
						{
							if(lCols[l]->isOn() && rCols[r]->isOn())
								ColliderCollision(lCols[l], rCols[r]);
						}
					}
				}
			}
			
		}
		else 
		{
			for (GameObject* lObj : lefts)
			{
				if (lObj->GetState() != GameObject::Active)
					continue;
				if (lObj->GetComponent<Collider2D>() == nullptr)
					continue;


				for (GameObject* rObj : rights)
				{
					if (rObj->GetState() != GameObject::Active)
						continue;
					if (rObj->GetComponent<Collider2D>() == nullptr)
						continue;
					if (lObj == rObj)
						continue;
					std::vector<Collider2D*>lCols = lObj->GetComponents<Collider2D>();
					std::vector<Collider2D*>rCols = rObj->GetComponents<Collider2D>();
					for (UINT l = 0; l < lCols.size(); l++)
					{
						for (UINT r = 0; r < rCols.size(); r++)
						{
							if (lCols[l]->isOn() && rCols[r]->isOn())
								ColliderCollision(lCols[l], rCols[r]);
						}
					}
				}

			}
		}

	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// 두 충돌체 레이어로 구성된 ID 확인
		ColliderID colliderID;
		colliderID.left = (UINT)left->GetID();
		colliderID.right = (UINT)right->GetID();

		// 이전 충돌 정보를 검색한다.
		// 만약에 충돌정보가 없는 상태라면
		// 충돌정보를 생성해준다.
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colliderID.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}

		// 충돌체크를 해준다.
		if (Intersect(left, right)) // 충돌을 한 상태
		{
			// 최초 충돌중 Enter
			if (iter->second == false)
			{
				if (left->IsTriiger())
					left->OnTriggerEnter(right);
				else
					left->OnCollisionEnter(right);

				if (right->IsTriiger())
					right->OnTriggerEnter(left);
				else
					right->OnCollisionEnter(left);

				iter->second = true;
			}
			else // 충돌 중이지 않은 상태 Enter
			{
				if (left->IsTriiger())
					left->OnTriggerStay(right);
				else
					left->OnCollisionStay(right);

				if (right->IsTriiger())
					right->OnTriggerStay(left);
				else
					right->OnCollisionStay(left);
			}
		}
		else // 충돌하지 않은상태
		{
			// 충돌 중인상태 Exit
			if (iter->second == true)
			{
				if (left->IsTriiger())
					left->OnTriggerExit(right);
				else
					left->OnCollisionExit(right);

				if (right->IsTriiger())
					right->OnTriggerExit(left);
				else
					right->OnCollisionExit(left);

				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		// Rect vs Rect
		
		static const Vector3 arrLocalPos[4] =
		{
			Vector3{-0.5f, 0.5f, 0.0f}
			,Vector3{0.5f, 0.5f, 0.0f}
			,Vector3{0.5f, -0.5f, 0.0f}
			,Vector3{-0.5f, -0.5f, 0.0f}
		};

		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();
		
		if (left->GetColliderType() == eColliderType::Rect
			&& right->GetColliderType() == eColliderType::Rect
			)
		{
			Matrix leftMat = leftTr->GetWorldMatrix();
			Matrix rightMat = rightTr->GetWorldMatrix();

			// 분리축 벡터 각 사각형의 높이와 너비 총 4가지
			Vector3 Axis[4] = {};
			Axis[0] = Vector3::Transform(arrLocalPos[1], leftMat);
			Axis[1] = Vector3::Transform(arrLocalPos[3], leftMat);
			Axis[2] = Vector3::Transform(arrLocalPos[1], rightMat);
			Axis[3] = Vector3::Transform(arrLocalPos[3], rightMat);

			Axis[0] -= Vector3::Transform(arrLocalPos[0], leftMat);
			Axis[1] -= Vector3::Transform(arrLocalPos[0], leftMat);
			Axis[2] -= Vector3::Transform(arrLocalPos[0], rightMat);
			Axis[3] -= Vector3::Transform(arrLocalPos[0], rightMat);

			for (size_t i = 0; i < 4; i++)
				Axis[i].z = 0.0f;

			Vector3 vc = left->GetPosition() - right->GetPosition();
			vc.z = 0.0f;

			Vector3 leftScale = Vector3(left->GetSize().x, left->GetSize().y, 1.0f);
			Axis[0] = Axis[0] * leftScale;
			Axis[1] = Axis[1] * leftScale;

			Vector3 rightScale = Vector3(right->GetSize().x, right->GetSize().y, 1.0f);
			Axis[2] = Axis[2] * rightScale;
			Axis[3] = Axis[3] * rightScale;

			Vector3 centerDir = vc;
			for (size_t i = 0; i < 4; i++)
			{
				//하나의 분리축을 기준으로 삼는다.
				//분리축을 표준화하고, 이 단위벡터에 모든 분리축을 투영시킨 벡터의 스칼라들을 구한다.
				//이 스칼라들의 합과 중심축 거리차 벡터의 내적값(투영시킨 벡터의 스칼라)을 비교하여 콜리전 여부 확인
				Vector3 vA = Axis[i];
				vA.Normalize();

				float projDist = 0.0f;
				for (size_t j = 0; j < 4; j++)
				{
					projDist += fabsf(Axis[j].Dot(vA) / 2.0f);
				}

				if (projDist < fabsf(centerDir.Dot(vA)))
				{
					return false;
				}
			}

			return true;
		}
		//Circle 
		else if (left->GetColliderType() == eColliderType::Circle
			&& right->GetColliderType() == eColliderType::Circle
			)
		{
			Vector3 vc = left->GetPosition() - right->GetPosition();
			float distance = vc.x * vc.x + vc.y * vc.y;
			distance = sqrtf(distance);
			if (left->GetRadius() + right->GetRadius() < distance)
				return false;

			return true;
		}
	}
}
