#include "DxLib.h"
#include<math.h>

const char TITLE[] = "�w�Дԍ����O�F�^�C�g��";

const int WIN_HEIGHT = 960;
const int WIN_WIDTH = 1280;

#define MAX 150

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);		//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(1.0);				//��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(0x00, 0x00, 0x00);		// ��ʂ̔w�i�F��ݒ肷��
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1)	return -1;



	int blocksize = 64;

	int x2 = 0;
	int y2 = 0;

	int playerR = 16;
	int playerX = 550;
	int playerY = 350;
	int playerSpeed = 2;

	int animalFlag = 0;
	int animal2Flag = 0;

	int animalX = 750;
	int animalY = 300;
	int animalR = 32;

	int animalX2 = 550;
	int animalY2 = 650;
	int animalSpeed = 1;
	int animal2Hit = 0;
	int animalHit = 0;

	int animal2PlayerX = 0;
	int animal2PlayerY = 0;
	int animal2Player = 0;

	int treeHit = 0;
	int treeFlag = 1;
	int count = 0;
	int treecount = 0;

	int brigeHit = 0;
	int bridgeFlag = 0;
	int bridgeCount = 0;

	int boatsHit = 0;
	int boatFlag = 0;

	int ground;
	ground = LoadGraph("ground.png");
	int gake;
	gake = LoadGraph("gake.png");
	int scen = 0;
	int hashigo;
	hashigo = LoadGraph("hashigo.png");
	int hashigo2;
	hashigo2 = LoadGraph("hashigo2.png");
	int map[14][20] = {
					 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,1,1,4,1,1,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,1,3,1,1,1,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,1,1,1,3,1,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };



	char keys[256] = { 0 };
	char oldkeys[256] = { 0 };

	float worldX = 0;
	float worldY = 0;

	// �Q�[�����[�v
	while (1)
	{
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		GetHitKeyStateAll(keys);
		ClearDrawScreen();
		x2 = playerX;
		y2 = playerY;
		//���͏���


		if (keys[KEY_INPUT_RIGHT] == 1) {
			playerX += playerSpeed;
		}

		if (keys[KEY_INPUT_LEFT] == 1) {
			playerX -= playerSpeed;
		}

		if (keys[KEY_INPUT_UP] == 1) {
			playerY -= playerSpeed;
		}

		if (keys[KEY_INPUT_DOWN] == 1) {
			playerY += playerSpeed;
		}

		if (animalHit == 1) {
			if (keys[KEY_INPUT_SPACE] == 1) {
				animalFlag = 1;
			}
		}

		if (boatsHit == 1) {
			if (treecount >= 1) {
				if (keys[KEY_INPUT_SPACE] == 1) {
					boatFlag = 1;
				}
			}
		}

		if (treecount >= 1) {
			if (brigeHit == 1) {
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
					bridgeFlag = 1;
					treecount--;
				}
			}
		}
		if (treeHit == 1) {
			if (keys[KEY_INPUT_SPACE] == 1) {
				count++;
			}
		}
		//�X�V����



		//worldX = playerX - 10;
		//worldY=playerY-;

		if (count == 100) {
			treeFlag = 0;
			count = 0;
			treecount++;
		}

		if (scen == 0) {



			//�}�b�v�`�b�v0
			//�E
			if (map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 0 &&
				map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 0) {
				playerX = x2;
			}
			//��
			if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 0 &&
				map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 0) {
				playerX = x2;
			}
			//��
			if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 0 &&
				map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 0) {
				playerY = y2;
			}
			//��
			if (map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 0 &&
				map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 0) {
				playerY = y2;
			}
			//����
			if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 0) {
				if (map[(playerY - playerR) / 64][(x2 - playerR) / 64] == 1) {
					if (playerX < x2) {
						playerX = x2;
					}
				}

				else if (map[(y2 - playerR) / 64][(playerX - playerR) / 64] == 1) {
					playerY = y2;
				}

				else
				{
					playerX = x2;
					playerY = y2;
				}
			}
			//����
			if (map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 0) {
				if (map[(playerY + playerR) / 64][(x2 - playerR) / 64] == 1) {
					if (playerX < x2) {
						playerX = x2;
					}
				}

				else if (map[(y2 + playerR) / 64][(playerX - playerR) / 64] == 1) {
					playerY = y2;
				}

				else
				{
					playerX = x2;
					playerY = y2;
				}
			}
			//�E��
			if (map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 0) {
				if (map[(playerY - playerR) / 64][(x2 + playerR) / 64] == 1) {
					if (playerX > x2) {
						playerX = x2;
					}
				}

				else if (map[(y2 - playerR) / 64][(playerX + playerR) / 64] == 1) {
					playerY = y2;
				}

				else
				{
					playerX = x2;
					playerY = y2;
				}
			}
			//�E��
			if (map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 0) {
				if (map[(playerY + playerR) / 64][(x2 + playerR) / 64] == 1) {
					if (playerX > x2) {
						playerX = x2;
					}
				}
				else if (map[(y2 + playerR) / 64][(playerX + playerR) / 64] == 1) {
					playerY = y2;
				}
				else
				{
					playerX = x2;
					playerY = y2;
				}
			}

			//�}�b�v�`�b�v2
			//�E
			if (map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 2 &&
				map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 2) {
				playerX = x2;
			}
			//��
			if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 2 &&
				map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 2) {
				playerX = x2;
			}
			//��
			if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 2 &&
				map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 2) {
				playerY = y2;
			}
			//��
			if (map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 2 &&
				map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 2) {
				playerY = y2;
			}
			//����
			if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 2) {
				if (map[(playerY - playerR) / 64][(x2 - playerR) / 64] == 1) {
					if (playerX < x2) {
						playerX = x2;
					}
				}

				else if (map[(y2 - playerR) / 64][(playerX - playerR) / 64] == 1) {
					playerY = y2;
				}

				else
				{
					playerX = x2;
					playerY = y2;
				}
			}
			//����
			if (map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 2) {
				if (map[(playerY + playerR) / 64][(x2 - playerR) / 64] == 1) {
					if (playerX < x2) {
						playerX = x2;
					}
				}

				else if (map[(y2 + playerR) / 64][(playerX - playerR) / 64] == 1) {
					playerY = y2;
				}

				else
				{
					playerX = x2;
					playerY = y2;
				}
			}
			//�E��
			if (map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 2) {
				if (map[(playerY - playerR) / 64][(x2 + playerR) / 64] == 1) {
					if (playerX > x2) {
						playerX = x2;
					}
				}

				else if (map[(y2 - playerR) / 64][(playerX + playerR) / 64] == 1) {
					playerY = y2;
				}

				else
				{
					playerX = x2;
					playerY = y2;
				}
			}
			//�E��
			if (map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 2) {
				if (map[(playerY + playerR) / 64][(x2 + playerR) / 64] == 1) {
					if (playerX > x2) {
						playerX = x2;
					}
				}
				else if (map[(y2 + playerR) / 64][(playerX + playerR) / 64] == 1) {
					playerY = y2;
				}
				else
				{
					playerX = x2;
					playerY = y2;
				}
			}

			//�}�b�v�`�b�v3
			//if (bridgeFlag == 0) {
				//�E
			if (treeFlag == 1) {
				if (map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 3 &&
					map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 3) {
					playerX = x2;
					treeHit = 1;
				}
				else {
					treeHit = 0;
				}
				//��
				if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 3 &&
					map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 3) {
					playerX = x2;
					treeHit = 1;
				}
				else {
					treeHit = 0;
				}
				//��
				if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 3 &&
					map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 3) {
					playerY = y2;
					treeHit = 1;
				}
				else {
					treeHit = 0;
				}
				//��
				if (map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 3 &&
					map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 3) {
					playerY = y2;
					treeHit = 1;
				}
				else {
					treeHit = 0;
				}
				//����
				if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 3) {
					if (map[(playerY - playerR) / 64][(x2 - playerR) / 64] == 1) {
						if (playerX < x2) {
							playerX = x2;
							treeHit = 1;
						}
					}

					else if (map[(y2 - playerR) / 64][(playerX - playerR) / 64] == 1) {
						playerY = y2;
						treeHit = 1;
					}

					else
					{
						playerX = x2;
						playerY = y2;
						treeHit = 1;
					}
				}
				//����
				if (map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 3) {
					if (map[(playerY + playerR) / 64][(x2 - playerR) / 64] == 1) {
						if (playerX < x2) {
							playerX = x2;
							treeHit = 1;
						}
					}

					else if (map[(y2 + playerR) / 64][(playerX - playerR) / 64] == 1) {
						playerY = y2;
						treeHit = 1;
					}

					else
					{
						playerX = x2;
						playerY = y2;
						treeHit = 1;
					}
				}
				//�E��
				if (map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 3) {
					if (map[(playerY - playerR) / 64][(x2 + playerR) / 64] == 1) {
						if (playerX > x2) {
							playerX = x2;
							treeHit = 1;
						}
					}

					else if (map[(y2 - playerR) / 64][(playerX + playerR) / 64] == 1) {
						playerY = y2;
						treeHit = 1;
					}

					else
					{
						playerX = x2;
						playerY = y2;
						treeHit = 1;
					}
				}
				//�E��
				if (map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 3) {
					if (map[(playerY + playerR) / 64][(x2 + playerR) / 64] == 1) {
						if (playerX > x2) {
							playerX = x2;
							treeHit = 1;
						}
					}
					else if (map[(y2 + playerR) / 64][(playerX + playerR) / 64] == 1) {
						playerY = y2;
						treeHit = 1;
					}
					else
					{
						playerX = x2;
						playerY = y2;
						treeHit = 1;
					}
				}
			}
			//�}�b�v�`�b�v4
			//�E
			if (map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 4 &&
				map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 4) {
				playerX = x2;
				boatsHit = 1;
			}
			//��
			if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 4 &&
				map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 4) {
				playerX = x2;
				boatsHit = 1;
			}
			//��
			if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 4 &&
				map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 4) {
				playerY = y2;
				boatsHit = 1;
			}
			//��
			if (map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 4 &&
				map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 4) {
				playerY = y2;
				boatsHit = 1;
			}
			//����
			if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 4) {
				if (map[(playerY - playerR) / 64][(x2 - playerR) / 64] == 1) {
					if (playerX < x2) {
						playerX = x2;
						boatsHit = 1;
					}
				}

				else if (map[(y2 - playerR) / 64][(playerX - playerR) / 64] == 1) {
					playerY = y2;
					boatsHit = 1;
				}

				else
				{
					playerX = x2;
					playerY = y2;
					boatsHit = 1;
				}
			}
			//����
			if (map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 4) {
				if (map[(playerY + playerR) / 64][(x2 - playerR) / 64] == 1) {
					if (playerX < x2) {
						playerX = x2;
						boatsHit = 1;
					}
				}

				else if (map[(y2 + playerR) / 64][(playerX - playerR) / 64] == 1) {
					playerY = y2;
					boatsHit = 1;
				}

				else
				{
					playerX = x2;
					playerY = y2;
					boatsHit = 1;
				}
			}
			//�E��
			if (map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 4) {
				if (map[(playerY - playerR) / 64][(x2 + playerR) / 64] == 1) {
					if (playerX > x2) {
						playerX = x2;
						boatsHit = 1;
					}
				}

				else if (map[(y2 - playerR) / 64][(playerX + playerR) / 64] == 1) {
					playerY = y2;
					boatsHit = 1;
				}

				else
				{
					playerX = x2;
					playerY = y2;
					boatsHit = 1;
				}
			}
			//�E��
			if (map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 4) {
				if (map[(playerY + playerR) / 64][(x2 + playerR) / 64] == 1) {
					if (playerX > x2) {
						playerX = x2;
						boatsHit = 1;
					}
				}
				else if (map[(y2 + playerR) / 64][(playerX + playerR) / 64] == 1) {
					playerY = y2;
					boatsHit = 1;
				}
				else
				{
					playerX = x2;
					playerY = y2;
					boatsHit = 1;
				}
			}
			//�}�b�v�`�b�v8
			if (bridgeFlag == 0) {
				//�E
				if (map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 8 &&
					map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 8) {
					playerX = x2;
					brigeHit = 1;
				}
				else {
					brigeHit = 0;
				}
				//��
				if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 8 &&
					map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 8) {
					playerX = x2;
					brigeHit = 1;
				}
				else {
					brigeHit = 0;
				}
				//��
				if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 8 &&
					map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 8) {
					playerY = y2;
					brigeHit = 1;
				}
				else {
					brigeHit = 0;
				}
				//��
				if (map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 8 &&
					map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 8) {
					playerY = y2;
					brigeHit = 1;
				}
				else {
					brigeHit = 0;
				}
				//����
				if (map[(playerY - playerR) / 64][(playerX - playerR) / 64] == 8) {
					if (map[(playerY - playerR) / 64][(x2 - playerR) / 64] == 1) {
						if (playerX < x2) {
							playerX = x2;
							brigeHit = 1;
						}
						else {
							brigeHit = 0;
						}
					}

					else if (map[(y2 - playerR) / 64][(playerX - playerR) / 64] == 1) {
						playerY = y2;
						brigeHit = 1;
					}

					else
					{
						playerX = x2;
						playerY = y2;
						brigeHit = 1;
					}
				}
				//����
				if (map[(playerY + playerR) / 64][(playerX - playerR) / 64] == 8) {
					if (map[(playerY + playerR) / 64][(x2 - playerR) / 64] == 1) {
						if (playerX < x2) {
							playerX = x2;
							brigeHit = 1;
						}
						else {
							brigeHit = 0;
						}
					}

					else if (map[(y2 + playerR) / 64][(playerX - playerR) / 64] == 1) {
						playerY = y2;
						brigeHit = 1;
					}

					else
					{
						playerX = x2;
						playerY = y2;
						brigeHit = 1;
					}
				}
				//�E��
				if (map[(playerY - playerR) / 64][(playerX + playerR) / 64] == 8) {
					if (map[(playerY - playerR) / 64][(x2 + playerR) / 64] == 1) {
						if (playerX > x2) {
							playerX = x2;
							brigeHit = 1;
						}
						else {
							brigeHit = 0;
						}
					}

					else if (map[(y2 - playerR) / 64][(playerX + playerR) / 64] == 1) {
						playerY = y2;
						brigeHit = 1;
					}

					else
					{
						playerX = x2;
						playerY = y2;
						brigeHit = 1;
					}
				}
				//�E��
				if (map[(playerY + playerR) / 64][(playerX + playerR) / 64] == 8) {
					if (map[(playerY + playerR) / 64][(x2 + playerR) / 64] == 1) {
						if (playerX > x2) {
							playerX = x2;
							brigeHit = 1;
						}
						else {
							brigeHit = 0;
						}
					}
					else if (map[(y2 + playerR) / 64][(playerX + playerR) / 64] == 1) {
						playerY = y2;
						brigeHit = 1;
					}
					else
					{
						playerX = x2;
						playerY = y2;
						brigeHit = 1;
					}
				}
			}

			if (animalFlag == 0) {
				animalX = animalX + animalSpeed;
				if (animalX >= 775) {
					animalSpeed = -animalSpeed;
				}
				else if (animalX <= 725) {
					animalSpeed = -animalSpeed;
				}
			}

			if (animalFlag == 0) {
				animal2PlayerX = animalX + animalR - playerX;
				animal2PlayerY = animalY + animalR - playerY;
				animal2Player = sqrtf(pow(animal2PlayerX, 2) + pow(animal2PlayerX, 2));

				if (animal2Player <= (animalR + playerR)) {
					animalHit = 1;
				}
			}

			if (animalFlag == 1) {
				animalSpeed = 0;
				animalY = playerY + 20;
				animalX = playerX - 10;
				animalSpeed = playerSpeed;
			}
		}
		//}


		//�`�揈��
		if (scen == 0) {
			for (int i = 0; i < 14; i++) {
				for (int j = 0; j < 20; j++) {
					if (map[i][j] == 0) {
						DrawBox(j * blocksize - worldX * 2, i * blocksize - worldY * 2, j * blocksize + blocksize - worldX * 2, i * blocksize + blocksize - worldY * 2, GetColor(0x00, 0x00, 0xdd), TRUE);
					}
					if (map[i][j] == 1) {
						DrawBox(j * blocksize - worldX * 2, i * blocksize - worldY * 2, j * blocksize + blocksize - worldX * 2, i * blocksize + blocksize - worldY * 2, GetColor(0x00, 0xaa, 0x00), TRUE);
					}
					if (map[i][j] == 2) {
						DrawBox(j * blocksize - worldX * 2, i * blocksize - worldY * 2, j * blocksize + blocksize - worldX * 2, i * blocksize + blocksize - worldY * 2, GetColor(0xff, 0xaa, 0x00), TRUE);
					}
					if (map[i][j] == 3) {
						if (treeFlag == 0) {
							DrawBox(j * blocksize - worldX * 2, i * blocksize - worldY * 2, j * blocksize + blocksize - worldX * 2, i * blocksize + blocksize - worldY * 2, GetColor(0x00, 0xaa, 0x00), TRUE);
						}
						if (treeFlag == 1) {
							DrawBox(j * blocksize - worldX * 2, i * blocksize - worldY * 2, j * blocksize + blocksize - worldX * 2, i * blocksize + blocksize - worldY * 2, GetColor(0x00, 0xdd, 0x00), TRUE);
							if (treeHit == 1) {
								DrawBox(j * blocksize - worldX * 2, i * blocksize - worldY * 2, j * blocksize + blocksize - worldX * 2, i * blocksize + blocksize - worldY * 2, GetColor(0x00, 0x00, 0x00), FALSE);
							}
						}
					}
					if (map[i][j] == 4) {
						if (treeHit == 1) {
							DrawBox(j * blocksize - worldX * 2, i * blocksize - worldY * 2, j * blocksize + blocksize - worldX * 2, i * blocksize + blocksize - worldY * 2, GetColor(0x00, 0x00, 0x00), FALSE);
						}
						if (boatFlag == 0) {
							DrawBox(j * blocksize - worldX * 2, i * blocksize - worldY * 2, j * blocksize + blocksize - worldX * 2, i * blocksize + blocksize - worldY * 2, GetColor(0xaa, 0xa0, 0x00), TRUE);
						}
						if (boatFlag == 1) {
							DrawBox(j * blocksize - worldX * 2, i * blocksize - worldY * 2, j * blocksize + blocksize - worldX * 2, i * blocksize + blocksize - worldY * 2, GetColor(0xdd, 0xa0, 0x00), TRUE);
						}
					}
					if (map[i][j] == 7) {
						DrawBox(j * blocksize - worldX * 2, i * blocksize - worldY * 2, j * blocksize + blocksize - worldX * 2, i * blocksize + blocksize - worldY * 2, GetColor(0x00, 0x00, 0xAA), TRUE);
					}

					if (map[i][j] == 8) {
						if (bridgeFlag == 0) {
							DrawBox(j * blocksize - worldX * 2, i * blocksize - worldY * 2, j * blocksize + blocksize - worldX * 2, i * blocksize + blocksize - worldY * 2, GetColor(0x00, 0x99, 0xdd), TRUE);
							if (treecount >= 1) {
								DrawBox(j * blocksize - worldX * 2, i * blocksize - worldY * 2, j * blocksize + blocksize - worldX * 2, i * blocksize + blocksize - worldY * 2, GetColor(0x00, 0x00, 0x00), FALSE);
							}
						}
						if (bridgeFlag == 1) {
							DrawBox(j * blocksize - worldX * 2, i * blocksize - worldY * 2, j * blocksize + blocksize - worldX * 2, i * blocksize + blocksize - worldY * 2, GetColor(0xff, 0xaa, 0x00), TRUE);
						}
					}
				}
			}
		}

		DrawBox(animalX, animalY, animalX + animalR, animalY + animalR, GetColor(0xff, 0xaa, 0x00), TRUE);
		DrawCircle(playerX, playerY, playerR, GetColor(0xff, 0xff, 0xff), TRUE);
		if (animal2Player <= animalR + playerR) {
			DrawBox(animalX, animalY, animalX + animalR, animalY + animalR, GetColor(0x00, 0x00, 0x00), FALSE);
		}



		DrawFormatString((WIN_WIDTH / 2) - playerR - 50, (WIN_HEIGHT + (WIN_HEIGHT - WIN_HEIGHT) / 2) - playerR - 50, GetColor(255, 255, 255), "����:map[%d][%d]", static_cast<int>((playerY - playerR) / blocksize), static_cast<int>((playerX - playerR) / blocksize));
		DrawFormatString((WIN_WIDTH / 2) - playerR - 50, (WIN_HEIGHT + (WIN_HEIGHT - WIN_HEIGHT) / 2) - playerR - 10, GetColor(255, 255, 255), "����:map[%d][%d]", static_cast<int>((playerY + playerR) / blocksize), static_cast<int>((playerX - playerR) / blocksize));
		DrawFormatString((WIN_WIDTH / 2) + playerR + 50, (WIN_HEIGHT + (WIN_HEIGHT - WIN_HEIGHT) / 2) - playerR - 50, GetColor(255, 255, 255), "�E��:map[%d][%d]", static_cast<int>((playerY - playerR) / blocksize), static_cast<int>((playerX + playerR) / blocksize));
		DrawFormatString((WIN_WIDTH / 2) + playerR + 50, (WIN_HEIGHT + (WIN_HEIGHT - WIN_HEIGHT) / 2) - playerR - 10, GetColor(255, 255, 255), "�E��:map[%d][%d]", static_cast<int>((playerY + playerR) / blocksize), static_cast<int>((playerX + playerR) / blocksize));
		DrawFormatString(0, 0, GetColor(0xff, 0xff, 0xff), "%d", count);
		DrawFormatString(30, 0, GetColor(0xff, 0xff, 0xff), "%d", treeFlag);
		DrawFormatString(40, 0, GetColor(0xff, 0xff, 0xff), "�؍�:%d", treecount);
		DrawFormatString(0, 25, GetColor(0xff, 0xff, 0xff), "�؂ɓ������Ă�:%d", treeHit);
		DrawFormatString(0, 50, GetColor(0xff, 0xff, 0xff), "�����˂����:%d", brigeHit);
		ScreenFlip();
		// 20�~���b�ҋ@�i�^��60FPS�j
		WaitTimer(20);
		// Windows �V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}
		// �d�r�b�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}