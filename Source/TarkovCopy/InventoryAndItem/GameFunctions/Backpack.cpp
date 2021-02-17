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
			//�ѹ� width ��ŭ �ǳ� �پ����� �ٽ� ���� ��Ų��.
			xIncrease = 1;

			//�ش�ĭ�� ����ٸ�
			UE_LOG(LogTemp, Warning, TEXT("Positions x : %d ,  y : %d  "), x, y)
				if (invenVisualize[x][y] == false)
				{
					//�� ��ó�� �������� width, height ��ŭ Ž��
					for (int startY = y; startY < y + pItemInfo->height; startY++)
					{
						for (int startX = x; startX < x + pItemInfo->width; startX++)
						{
							//startX�� �κ� ũ�⸦ ����� ���� ���� ó��
							if (startX >= capacityWidth)
							{
								spaceXCount = 0;
								break;
							}

							//�ش� �κ��� ���࿡ ��ĭ�� �ϳ��� ��°�� ������.
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
					//�ش� ������ ����� �� �ִ� �����̸� ���ڸ����� ������ �ƴϸ� ��� Ž��
					if (spaceXCount >= pItemInfo->width && spaceYCount >= pItemInfo->height)
					{
						//TODO:tuple��  �����ǵ� ���� �����Ұ�.
						return  std::tuple<bool, int, int>(true, x, y);
					}
					else
					{
						//�̹� width ��ŭ �ش� ������ �˻��߱� ������ ���� �������� �н� ��Ų��.
						xIncrease += pItemInfo->width;
					}
				}
		}
	}
	//�̹� ���ܰ迡�� üũ�� ���ߴٸ� ���ٴ� ���̹Ƿ� ��������.
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
			//�ѹ� height ��ŭ �ǳ� �پ����� �ٽ� ���� ��Ų��.
			yIncrease = 1;

			//�ش�ĭ�� ����ٸ�
			if (invenVisualize[x][y] == false)
			{
				//�� ��ó�� �������� width, height ��ŭ Ž��
				for (int startY = y; startY < y + pItemInfo->height; startY++)
				{
					for (int startX = x; startX < x + pItemInfo->width; startX++)
					{

						if (startY >= capacityHeight)
						{
							spaceYCount = 0;
							break;
						}

						//�ش� �κ��� ���࿡ ��ĭ�� �ϳ��� ��°�� ������.
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

				//�ش� ������ ����� �� �ִ� �����̸� ���ڸ����� ������ �ƴϸ� ��� Ž��
				if (spaceXCount == pItemInfo->width && spaceYCount == pItemInfo->height)
				{
					//TODO:tuple��  �����ǵ� ���� �����Ұ�.
					return  std::tuple<bool, int, int>(true, x, y);
				}
				else
				{
					//�̹� height ��ŭ �ش� ������ �˻��߱� ������ ���� �������� �н� ��Ų��.
					yIncrease += pItemInfo->height;
				}
			}
		}
	}
	//�̹� ���ܰ迡�� üũ�� ���ߴٸ� ���ٴ� ���̹Ƿ� ��������.
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
	//TODO: ������ ���ڸ� ã�Ƽ� �߰� 
	std::tuple<bool, int, int> results = HasEmptySpace(pItemInfo); //�ڸ� ���� , �ش� �������� left,top
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
