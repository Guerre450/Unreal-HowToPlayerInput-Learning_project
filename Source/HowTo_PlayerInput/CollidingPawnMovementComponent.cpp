// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponent.h"


void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction){
    Super::TickComponent(DeltaTime,TickType,ThisTickFunction);


    // Make sure that everything is still valid, and that we are allowed to move.
    // if no pawn that owns this component, if we can move and update and if component update should be skipped
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)){
        return;
    }
    // Get (and then clear) the movement vector that we set in ACollidingPawn::Tick
    FVector DesiredMovementForThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
    if (!DesiredMovementForThisFrame.IsNearlyZero()){
        FHitResult Hit;
        SafeMoveUpdatedComponent(DesiredMovementForThisFrame,UpdatedComponent->GetComponentRotation(),true,Hit);

        // If we bumped into something, try to slide along it
            if(Hit.IsValidBlockingHit()){
                SlideAlongSurface(DesiredMovementForThisFrame,1.0f - Hit.Time,Hit.Normal,Hit);
            }
    }

}

