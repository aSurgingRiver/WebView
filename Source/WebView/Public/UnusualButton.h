// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "Widgets/Input/SButton.h"
#include "Engine/Texture2D.h"
namespace syt {
	class SUnusualButton : public SButton
	{
	public:

		SUnusualButton();
		~SUnusualButton();

		virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

		virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;

		virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

		virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

		virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;

		virtual TSharedPtr<IToolTip> GetToolTip() override;

	protected:
		UTexture2D* GetHitTexture();
		UTexture2D* LoadTexture(const FString& ImagePath);
	private:
		UTexture2D* HitTexutre;
	};

}