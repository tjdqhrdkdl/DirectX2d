#include "yaGroundScript.h"
#include "yaRigidBody.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaCollider2D.h"
#include "yaPlayerScript.h"
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
		if (collider->isJumpBox() && rb && rb->isFalling())
		{
			rb->SetGround(true);
			Transform* rbTr = colObj->GetComponent<Transform>();
			Transform* grTr = GetComponent<Transform>();
			Vector3 rbPos = rbTr->GetPosition();
			Vector3 grPos = grTr->GetPosition();

			rbPos.y = grPos.y + colObj->GetComponent<Collider2D>()->GetScale().y/2 + GetComponent<Collider2D>()->GetScale().y/2;

			rbTr->SetPosition(rbPos);
			
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
	}

	void Ground::OnCollisionExit(Collider2D* collider)
	{
		Rigidbody* rb = collider->GetOwner()->GetComponent<Rigidbody>();
		if (collider->isJumpBox() && rb)
		{
			rb->SetGround(false);
			if (rb->GetOwner()->GetComponent<Player>())
				rb->GetOwner()->GetComponent<Player>()->Fall();
		}
	}

}