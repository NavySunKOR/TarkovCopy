// Fill out your copyright notice in the Description page of Project Settings.

#include <Layout/SlateRect.h>
#include "Backpack.h"

Backpack::Backpack()
{
}

Backpack::~Backpack()
{
}

void Backpack::Init()
{
	invenVisualize = new bool*[capacityWidth];
	for (int i = 0; i < capacityWidth; i++)
	{
		invenVisualize[i] = new bool[capacityHeight];
	}

	for (int i = 0; i < capacityWidth; i++)
	{
		for (int j = 0; j < capacityHeight; j++)
		{
			invenVisualize[i, j] = false;
		}
	}
}

bool Backpack::HasEmptySpaceWidthAxis(UItemInfo* pItemInfo)
{
	int spaceXCount = 0;
	int spaceYCount = 0;

	for (int y = 0; y < capacityHeight; y++)
	{
		int xIncrease = 1;
		for (int x = 0; x < capacityWidth; x += xIncrease)
		{
			//한번 width 만큼 건너 뛰었으면 다시 리셋 시킨다.
			xIncrease = 1;

			//해당칸이 비었다면
			if (invenVisualize[x, y] == false)
			{
				//그 근처를 아이템의 width, height 만큼 탐색
				for (int startY = y; startY < y + pItemInfo->height; y++)
				{
					for (int startX = x; startX < x + pItemInfo->width; x++)
					{
						//해당 인벤에 만약에 빈칸이 하나라도 통째로 무쓸모.
						if (invenVisualize[startX, startY] == false)
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
					return true;
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
	return false;
}


bool Backpack::HasEmptySpaceHeightAxis(UItemInfo* pItemInfo)
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
			if (invenVisualize[x, y] == false)
			{
				//그 근처를 아이템의 width, height 만큼 탐색
				for (int startY = y; startY < y + pItemInfo->height; y++)
				{
					for (int startX = x; startX < x + pItemInfo->width; x++)
					{
						//해당 인벤에 만약에 빈칸이 하나라도 통째로 무쓸모.
						if (invenVisualize[startX, startY] == false)
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
					return true;
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
	return false;
}

bool Backpack::HasEmptySpace(UItemInfo* pItemInfo)
{
	if (pItemInfo->width >= pItemInfo->height)
	{
		return HasEmptySpaceWidthAxis(pItemInfo);
	}
	else
	{
		return HasEmptySpaceHeightAxis(pItemInfo);
	}


	return true;
}


bool Backpack::IsIntersected(UItemInfo* pItemInfo)
{
	for (int i = 0; i < itemContainers.Num(); i++)
	{
		if (FSlateRect::DoRectanglesIntersect(itemContainers[i]->rect, pItemInfo->rect))
			return true;
	}
	return false;
}

void Backpack::AddItem(UItemInfo* pItemInfo)
{
	//TODO: 아이템 빈자리 찾아서 추가 
	if (HasEmptySpace(pItemInfo))
	{
		itemContainers.Add(pItemInfo);
	}
}



