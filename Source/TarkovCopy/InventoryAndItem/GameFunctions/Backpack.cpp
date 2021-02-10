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
			//�ѹ� width ��ŭ �ǳ� �پ����� �ٽ� ���� ��Ų��.
			xIncrease = 1;

			//�ش�ĭ�� ����ٸ�
			if (invenVisualize[x, y] == false)
			{
				//�� ��ó�� �������� width, height ��ŭ Ž��
				for (int startY = y; startY < y + pItemInfo->height; y++)
				{
					for (int startX = x; startX < x + pItemInfo->width; x++)
					{
						//�ش� �κ��� ���࿡ ��ĭ�� �ϳ��� ��°�� ������.
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

				//�ش� ������ ����� �� �ִ� �����̸� ���ڸ����� ������ �ƴϸ� ��� Ž��
				if (spaceXCount == pItemInfo->width && spaceYCount == pItemInfo->height)
				{
					//TODO:tuple��  �����ǵ� ���� �����Ұ�.
					return true;
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
			//�ѹ� height ��ŭ �ǳ� �پ����� �ٽ� ���� ��Ų��.
			yIncrease = 1;

			//�ش�ĭ�� ����ٸ�
			if (invenVisualize[x, y] == false)
			{
				//�� ��ó�� �������� width, height ��ŭ Ž��
				for (int startY = y; startY < y + pItemInfo->height; y++)
				{
					for (int startX = x; startX < x + pItemInfo->width; x++)
					{
						//�ش� �κ��� ���࿡ ��ĭ�� �ϳ��� ��°�� ������.
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

				//�ش� ������ ����� �� �ִ� �����̸� ���ڸ����� ������ �ƴϸ� ��� Ž��
				if (spaceXCount == pItemInfo->width && spaceYCount == pItemInfo->height)
				{
					//TODO:tuple��  �����ǵ� ���� �����Ұ�.
					return true;
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
	//TODO: ������ ���ڸ� ã�Ƽ� �߰� 
	if (HasEmptySpace(pItemInfo))
	{
		itemContainers.Add(pItemInfo);
	}
}



