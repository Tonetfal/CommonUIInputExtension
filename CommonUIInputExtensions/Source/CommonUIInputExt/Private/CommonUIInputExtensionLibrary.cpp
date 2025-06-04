// Author: Antonio Sidenko (Tonetfal), April 2024

#include "CommonUIInputExtensionLibrary.h"

#include "CommonUITypes.h"
#include "CommonUserWidget.h"
#include "Input/CommonUIActionRouterBase.h"
#include "Input/CommonUIInputTypes.h"

template<typename T>
static FCUIE_InputActionBindingHandle CommonUIInputExtension_RegisterBinding(
	UCommonUserWidget* Target, const T& InputAction, const FCUIE_BindUIActionArgs& Arguments)
{
	FCUIE_InputActionBindingHandle ReturnValue;
	if (!IsValid(Target))
	{
		return ReturnValue;
	}

	FBindUIActionArgs BindArgs(InputAction, FSimpleDelegate::CreateLambda([Arguments]
	{
		const bool bExecuted = Arguments.Callback.ExecuteIfBound();
	}));

	BindArgs.KeyEvent = Arguments.KeyEvent;
	BindArgs.bConsumeInput = Arguments.bConsumeInput;
	BindArgs.bIsPersistent = Arguments.bIsPersistent;
	BindArgs.bDisplayInActionBar = Arguments.bDisplayInActionBar;

	if (auto* ActionRouter = UCommonUIActionRouterBase::Get(*Target); IsValid(ActionRouter))
	{
		ReturnValue.Handle = ActionRouter->RegisterUIActionBinding(*Target, BindArgs);
	}

	return ReturnValue;
}

FCUIE_InputActionBindingHandle UCommonUIInputExtensionLibrary::RegisterBinding_CommonUI(
	UCommonUserWidget* Target, FDataTableRowHandle InputAction, const FCUIE_BindUIActionArgs& Arguments)
{
	return CommonUIInputExtension_RegisterBinding(Target, InputAction, Arguments);
}

FCUIE_InputActionBindingHandle UCommonUIInputExtensionLibrary::RegisterBinding_EnhancedInput(
	UCommonUserWidget* Target, const UInputAction* InputAction, const FCUIE_BindUIActionArgs& Arguments)
{
	FCUIE_InputActionBindingHandle ReturnValue;
	if (ensureMsgf(CommonUI::IsEnhancedInputSupportEnabled(),
		TEXT("Impossible to bind an Enhanced Input Input Action [%s] with widget [%s] ")
		TEXT("if Common UI Enhanced Input support is not enabled."), *GetNameSafe(InputAction), *GetNameSafe(Target)))
	{
		if (ensureMsgf(IsValid(InputAction), TEXT("Impossible to bind an invalid Input Action to widget [%s]"),
			*GetNameSafe(Target)))
		{
			ReturnValue = CommonUIInputExtension_RegisterBinding(Target, InputAction, Arguments);
		}
	}

	return ReturnValue;
}

void UCommonUIInputExtensionLibrary::UnregisterBinding(FCUIE_InputActionBindingHandle BindingHandle)
{
	BindingHandle.Handle.Unregister();
}
