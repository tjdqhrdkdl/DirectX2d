#include "yaGroundScript.h"
#include "yaRigidBody.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaCollider2D.h"
#include "yaPlayer.h"
namespace ya
{
	Ground::Ground()
	{
	}

	Ground::~Ground()
	{
	}

	void Ground::Initialize()
	{
		Collider2D* col = AddComponent<Collider2D>();
		col->Initialize();
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(10, 1));
		GameObject::Initialize();
	}

	void Ground::Update()
	{
		GameObject::Update();

	}

	void Ground::FixedUpdate()
	{
		GameObject::FixedUpdate();

	}

	void Ground::Render()
	{
		GameObject::Render();

	}

	void Ground::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* colObj = collider->GetOwner();
		Rigidbody* rb = colObj->GetComponent<Rigidbody>();
		Transform* colTr = colObj->GetComponent<Transform>();
		Transform* grTr = GetComponent<Transform>();
		Vector3 colPos = colTr->GetPosition();
		Vector3 grPos = grTr->GetPosition();
		Collider2D* grCol = GetComponent<Collider2D>();
		if (collider->isJumpBox() && rb && rb->isFalling())
		{
			if (colPos.y + colObj->GetComponent<Collider2D>()->GetScale().y / 2  < grPos.y + grCol->GetScale().y / 2)
			{
				if (colPos.x < grPos.x)
					colPos.x = grPos.x - grCol->GetScale().x / 2 - colObj->GetComponent<Collider2D>()->GetScale().x/2 - 0.05;
				else
					colPos.x = grPos.x + grCol->GetScale().x / 2 + colObj->GetComponent<Collider2D>()->GetScale().x / 2 + 0.05;

			}
			else
			{
				rb->SetGround(true);
				colPos.y = grPos.y + colObj->GetComponent<Collider2D>()->GetScale().y / 2 + grCol->GetScale().y / 2;
			}

			colTr->SetPosition(colPos);
		}
	}

	void Ground::OnCollisionStay(Collider2D* collider)
	{
		GameObject* colObj = collider->GetOwner();
		Rigidbody* rb = colObj->GetComponent<Rigidbody>();
		if (collider->isJumpBox() && rb && rb->isGround())
		{
			Transform* rbTr = colObj->GetComponent<Transform>();
			Transform* grTr = GetComponent<Transform>();
			Vector3 rbPos = rbTr->GetPosition();
			Vector3 grPos = grTr->GetPosition();

			rbPos.y = grPos.y + colObj->GetComponent<Collider2D>()->GetScale().y / 2 + GetComponent<Collider2D>()->GetScale().y / 2;

			rbTr->SetPosition(rbPos);

		}
		else if (collider->isJumpBox() && rb && !(rb->isGround()))
		{

			Transform* colTr = colObj->GetComponent<Transform>();
			Transform* grTr = GetComponent<Transform>();
			Vector3 colPos = colTr->GetPosition();
			Vector3 grPos = grTr->GetPosition();
			Collider2D* grCol = GetComponent<Collider2D>();
			if (colPos.y + colObj->GetComponent<Collider2D>()->GetScale().y / 2 < grPos.y + grCol->GetScale().y / 2)
			{
				if (colPos.x < grPos.x)
					colPos.x -= 0.01;
			}
		}
	}

	void Ground::OnCollisionExit(Collider2D* collider)
	{
		Rigidbody* rb = collider->GetOwner()->GetComponent<Rigidbody>();
		if (collider->isJumpBox() && rb)
		{
			rb->SetGround(false);
			if (rb->GetOwner()->GetLayerType()== eLayerType::Player)
				dynamic_cast<Player*>(rb->GetOwner())->Fall();
		}
	}

}