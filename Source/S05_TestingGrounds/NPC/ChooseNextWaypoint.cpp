// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolRoute.h" // TODO Remove
#include "AIController.h"
#include "ChooseNextWaypoint.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController *  AIController = OwnerComp.GetAIOwner();
	if (!ensure(AIController)) { return EBTNodeResult::Failed; }
	APawn * ControlledPawn = AIController->GetPawn();

	UBlackboardComponent * BlackboardComp = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	

	
	//Get Patrol Points
	UPatrolRoute * PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }
	TArray<AActor*> PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num()==0) { UE_LOG(LogTemp, Warning, TEXT("No patrol points")); return EBTNodeResult::Failed; }

	//Set next waypoint
	AActor * NextWaypoint = PatrolPoints[Index];
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, NextWaypoint);

	//Cycle Index
	Index = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	return EBTNodeResult::Succeeded;
}


