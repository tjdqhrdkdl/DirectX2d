#include "yaGroundScript.h"
#include "yaRigidBody.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaCollider2D.h"
#include "yaPlayerScript.h"
namespace ya
{
	GroundScript::GroundScript()
	{
	}

	GroundScript::~GroundScript()
	{
	}

	void GroundScript::Initialize()
	{
		Collider2D* col = GetOwner()->AddComponent<Collider2D>();
		col->Initialize();
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(10, 1));
	}

	void GroundScript::Update()
	{
	}

	void GroundScript::FixedUpdate()
	{
	}

	void GroundScript::Render()
	{
	}

	void GroundScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* colObj = collider->GetOwner();
		Rigidbody* rb = colObj->GetComponent<Rigidbody>();
		if (collider->isJumpBox() && rb && rb->isFalling())
		{
			rb->SetGround(true);
			Transform* rbTr = colObj->GetComponent<Transform>();
			Transform* grTr = GetOwner()->GetComponent<Transform>();
			Vector3 rbPos = rbTr->GetPosition();
			Vector3 grPos = grTr->GetPosition();

			rbPos.y = grPos.y + colObj->GetComponent<Collider2D>()->GetScale().y;

			rbTr->SetPosition(rbPos);
			
		}
	}

	void GroundScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void GroundScript::OnCollisionExit(Collider2D* collider)
	{
		Rigidbody* rb = collider->GetOwner()->GetComponent<Rigidbody>();
		if (collider->isJumpBox() && rb)
		{
			if (rb->GetOwner()->GetComponent<PlayerScript>())
				rb->GetOwner()->GetComponent<PlayerScript>()->Fall();
		}
	}

}