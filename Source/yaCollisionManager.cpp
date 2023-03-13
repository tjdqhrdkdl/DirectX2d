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

					ColliderCollision(lObj->GetComponent<Collider2D>(), rObj->GetComponent<Collider2D>());
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

					ColliderCollision(lObj->GetComponent<Collider2D>(), rObj->GetComponent<Collider2D>());
				}

			}
		}

	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// �� �浹ü ���̾�� ������ ID Ȯ��
		ColliderID colliderID;
		colliderID.left = (UINT)left->GetID();
		colliderID.right = (UINT)right->GetID();

		// ���� �浹 ������ �˻��Ѵ�.
		// ���࿡ �浹������ ���� ���¶��
		// �浹������ �������ش�.
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colliderID.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}

		// �浹üũ�� ���ش�.
		if (Intersect(left, right)) // �浹�� �� ����
		{
			// ���� �浹�� Enter
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
			else // �浹 ������ ���� ���� Enter
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
		else // �浹���� ��������
		{
			// �浹 ���λ��� Exit
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
		// 0 --- 1
		// |     |
		// 3 --- 2
		
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

			// �и��� ���� �� �簢���� ���̿� �ʺ� �� 4����
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

			Vector3 centerDir = vc;
			for (size_t i = 0; i < 4; i++)
			{
				//�ϳ��� �и����� �������� ��´�.
				//�и����� ǥ��ȭ�ϰ�, �� �������Ϳ� ��� �и����� ������Ų ������ ��Į����� ���Ѵ�.
				//�� ��Į����� �հ� �߽��� �Ÿ��� ������ ������(������Ų ������ ��Į��)�� ���Ͽ� �ݸ��� ���� Ȯ��
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
		/*
		else if (left->GetColliderType() != right->GetColliderType())
		{
			Matrix mat;
			float radius;
			if (left->GetColliderType() == eColliderType::Rect)
			{
				mat = leftTr->GetWorldMatrix();
				radius = right->GetRadius();
			}
			else
			{
				mat = rightTr->GetWorldMatrix();
				radius = left->GetRadius();
			}
			Vector3 points[4];
			for (size_t i = 0; i < 4; i++)
			{
				points[i] = Vector3::Transform(arrLocalPos[i], mat);
			}
			for (size_t i = 4; i == 0; i++)
			{

				if (points[i + 1].x < points[i].x)
					std::swap(points[i + 1], points[i]);

			}

			
			
		}*/
	}
}
