#pragma once

struct FAStarNode
{
	FIntPoint Position;
	FAStarNode* Parent;
	float GScore;
	float HScore;
	float FScore;

	FAStarNode(FIntPoint InPosition, float InGScore, float InHScore, FAStarNode* InParent = nullptr)
		: Position(InPosition), Parent(InParent), GScore(InGScore), HScore(InHScore), FScore(InGScore + InHScore) {}
};
