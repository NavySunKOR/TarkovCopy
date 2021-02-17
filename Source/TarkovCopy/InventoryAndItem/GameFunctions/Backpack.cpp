// Fill out your copyright notice in the Description page of Project Settings.

#include <Layout/SlateRect.h>
#include "Backpack.h"

void UBackpack::Init(int pCapacityWidth, int pCapacityHeight)
{
	capacityWidth = pCapacityWidth;
	capacityHeight = pCapacityHeight;

	invenVisualize = new bool* [capacityWidth];
	for (int i = 0; i < capacityWidth; i++)
	{
		invenVisualize[i] = new bool[capacityHeight];
	}

	for (int i = 0; i < capacityWidth; i++)
	{
		for (int j = 0; j < capacityHeight; j++)
		{
			invenVisualize[i][j] = false;

			UE_LOG(LogTemp, Warning, TEXT("inven x : %d , y : %d , val : %d"), i, j, invenVisualize[i][j])
		}
	}
}

std::tuple<bool, int, int> UBackpack::HasEmptySpaceWidthAxis(UItemInfo* pItemInfo)
{
	int spaceXCount = 0;
	int spaceYCount = 0;
	int xIncrease = 1;

	for (int y = 0; y < capacityHeight; y++)
	{
		for (int x = 0; x < capacityWidth; x += xIncrease)
		{
			//한번 width 만큼 건너 뛰었으면 다시 리셋 시킨다.
			xIncrease = 1;

			//해당칸이 비었다면
			UE_LOG(LogTemp, Warning, TEXT("Positions x : %d ,  y : %d  "), x, y)
				if (invenVisualize[x][y] == false)
				{
					//그 근처를 아이템의 width, height 만큼 탐색
					for (int startY = y; startY < y + pItemInfo->height; startY++)
					{
						for (int startX = x; startX < x + pItemInfo->width; startX++)
						{
							//startX가 인벤 크기를 벗어나면 공간 없음 처리
							if (startX >= capacityWidth)
							{
								spaceXCount = 0;
								break;
							}

							//해당 인벤에 만약에 빈칸이 하나라도 통째로 무쓸모.
							if (invenVisualize[startX][startY] == false)
							{
								spaceXCount++;
							}
							else
							{
								spaceXCount = 0;
								break;
							}
						}
						if (spaceXCount == 0)
						{
							spaceYCount = 0;
							break;
						}
						else
						{
							spaceYCount++;
						}
					}

					UE_LOG(LogTemp, Warning, TEXT("Total spaceXCount :%d , spaceYCount : %d"), spaceXCount, spaceYCount);
					//해당 공간이 사용할 수 있는 공간이면 그자리에서 끝내고 아니면 계속 탐색
					if (spaceXCount >= pItemInfo->width && spaceYCount >= pItemInfo->height)
					{
						//TODO:tuple로  포지션도 같이 리턴할것.
						return  std::tuple<bool, int, int>(true, x, y);
					}
					else
					{
						//이미 width 만큼 해당 지점을 검색했기 때문에 다음 지점으로 패스 시킨다.
						xIncrease += pItemInfo->width;
					}
				}
		}
	}
	//이미 윗단계에서 체크를 못했다면 없다는 것이므로 빠져나감.
	return std::tuple<bool, int, int>(false, -1, -1);
}


std::tuple<bool, int, int> UBackpack::HasEmptySpaceHeightAxis(UItemInfo* pItemInfo)
{
	int spaceXCount = 0;
	int spaceYCount = 0;

	for (int x = 0; x < capacityWidth; x++)
	{
		int yIncrease = 1;
		for (int y = 0; y < capacityHeight; y += yIncrease)
		{
			//한번 height 만큼 건너 뛰었으면 다시 리셋 시킨다.
			yIncrease = 1;

			//해당칸이 비었다면
			if (invenVisualize[x][y] == false)
			{
				//그 근처를 아이템의 width, height 만큼 탐색
				for (int startY = y; startY < y + pItemInfo->height; startY++)
				{
					for (int startX = x; startX < x + pItemInfo->width; startX++)
					{

						if (startY >= capacityHeight)
						{
							spaceYCount = 0;
							break;
						}

						//해당 인벤에 만약에 빈칸이 하나라도 통째로 무쓸모.
						if (invenVisualize[startX][startY] == false)
						{
							spaceXCount++;
						}
						else
						{
							spaceXCount = 0;
							break;
						}
					}
					if (spaceXCount == 0)
					{
						spaceYCount = 0;
						break;
					}
					else
					{
						spaceYCount++;
					}
				}

				//해당 공간이 사용할 수 있는 공간이면 그자리에서 끝내고 아니면 계속 탐색
				if (spaceXCount == pItemInfo->width && spaceYCount == pItemInfo->height)
				{
					//TODO:tuple로  포지션도 같이 리턴할것.
					return  std::tuple<bool, int, int>(true, x, y);
				}
				else
				{
					//이미 height 만큼 해당 지점을 검색했기 때문에 다음 지점으로 패스 시킨다.
					yIncrease += pItemInfo->height;
				}
			}
		}
	}
	//이미 윗단계에서 체크를 못했다면 없다는 것이므로 빠져나감.
	return std::tuple<bool, int, int>(false, -1, -1);
}

void UBackpack::UpdateInvenVisualize(UItemInfo* pItemInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("Update Visualize - top : %d , height : %d"), pItemInfo->top, pItemInfo->top + pItemInfo->height);
	UE_LOG(LogTemp, Warning, TEXT("Update Visualize - left : %d , width : %d"), pItemInfo->left, pItemInfo->left + pItemInfo->width);
	for (int y = pItemInfo->top; y < pItemInfo->top + pItemInfo->height; y++)
	{
		for (int x = pItemInfo->left; x < pItemInfo->left + pItemInfo->width; x++)
		{
			invenVisualize[x][y] = true;
		}
	}

}

std::tuple<bool, int, int> UBackpack::HasEmptySpace(UItemInfo* pItemInfo)
{
	if (pItemInfo->width >= pItemInfo->height)
	{
		UE_LOG(LogTemp, Warning, TEXT("Width!!"))
			return HasEmptySpaceWidthAxis(pItemInfo);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Height!!"))
			return HasEmptySpaceHeightAxis(pItemInfo);
	}


	return std::tuple<bool, int, int>(false, -1, -1);
}


bool UBackpack::IsIntersected(UItemInfo* pItemInfo)
{
	for (int i = 0; i < itemContainers.Num(); i++)
	{
		if (FSlateRect::DoRectanglesIntersect(itemContainers[i]->rect, pItemInfo->rect))
			return true;
	}
	return false;
}

bool UBackpack::AddItem(UItemInfo* pItemInfo)
{
	//TODO: 아이템 빈자리 찾아서 추가 
	std::tuple<bool, int, int> results = HasEmptySpace(pItemInfo); //자리 여부 , 해당 아이템의 left,top
	UE_LOG(LogTemp, Warning, TEXT("results : %d"), std::get<0>(results));
	if (std::get<0>(results))
	{
		pItemInfo->InitRect(std::get<1>(results), std::get<2>(results));
		UpdateInvenVisualize(pItemInfo);
		itemContainers.Add(pItemInfo);
		return true;
	}
	else
	{
		return false;
	}
}

FVector2D UBackpack::GetBackpackSize()
{
	return FVector2D(capacityWidth,capacityHeight);
}
