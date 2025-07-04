// Author: Antonio Sidenko (Tonetfal), April 2024

#pragma once

#include "CommonInputModeTypes.h"
#include "InputAction.h"
#include "Input/UIActionBindingHandle.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "CommonUIInputExtensionLibrary.generated.h"

class UCommonUserWidget;

DECLARE_DYNAMIC_DELEGATE(FInputActionExecutedSignature);

USTRUCT(BlueprintType)
struct FCUIE_InputActionBindingHandle
{
	GENERATED_BODY()

public:
	FUIActionBindingHandle Handle;
};

USTRUCT(BlueprintType)
struct FCUIE_BindUIActionArgs
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EInputEvent> KeyEvent = IE_Pressed;

	/**
	 * A persistent binding is always registered and will be executed regardless of the activation status of the binding widget's parentage.
	 * Persistent bindings also never stomp one another - if two are bound to the same action, both will execute. Use should be kept to a minimum.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPersistent = false;

	/**
	 * True to have this binding consume the triggering key input.
	 * Persistent bindings that consume will prevent the key reaching non-persistent bindings and game agents.
	 * Non-persistent bindings that consume will prevent the key reaching game agents.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bConsumeInput = true;

	/** Whether this binding can/should be displayed in a CommonActionBar (if one exists) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDisplayInActionBar = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECommonInputMode InputMode = ECommonInputMode::Menu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInputActionExecutedSignature Callback;
};

UCLASS()
class UCommonUIInputExtensionLibrary
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Target", Keywords="input action"))
	static FCUIE_InputActionBindingHandle RegisterBinding_CommonUI(UCommonUserWidget* Target,
		FDataTableRowHandle InputAction, const FCUIE_BindUIActionArgs& Arguments);

	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Target", Keywords="input action"))
	static FCUIE_InputActionBindingHandle RegisterBinding_EnhancedInput(UCommonUserWidget* Target,
		const UInputAction* InputAction, const FCUIE_BindUIActionArgs& Arguments);

	UFUNCTION(BlueprintCallable)
	static void UnregisterBinding(FCUIE_InputActionBindingHandle BindingHandle);
};
