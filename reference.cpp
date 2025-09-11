#define CANVAS_UPPER_LENGTH		5
#define CANVAS_MIDDLE_LENGTH 	8
#define CANVAS_LOWER_LENGTH		5

static uint8_t list_descent_time_cnt[8] = { 0 }; 		// �½�ʱ�������
static uint8_t list_descent_speed[8] = { 0 };		// �½��ٶ�
static int8_t list_head_position[8] = { 0 };		// ��ͷλ��
static uint32_t list_color[8] = { 0 };			// ����ɫ
// static uint8_t list_head_brightness[8] = {0};	// ��ͷ����
static uint8_t list_len[8] = { 0 };				// �г��� 3-5

void app_display_func_5_init_list(uint8_t i)
{
	// ��ʼ���½��ٶ�
	srand(i + stimer_get_systime());
	list_descent_speed[i] = rand() % 30 + 3;

	// ��ʼ����ͷ��λ��
	srand(i + stimer_get_systime());
	list_head_position[i] = (rand() % CANVAS_UPPER_LENGTH);

	// ��ʼ����ɫ
	list_color[i] = 0x00FF00;

	// // ��ʼ����
	// for (uint8_t i = 0;i<8;i++)
	// {
	// 	srand(stimer_get_systime()+i);
	// 	list_head_brightness[i] = (rand() % 100) + 20;
	// }

	// �г���
	srand(i + stimer_get_systime());
	list_len[i] = (rand() % 3) + 4;
}


// ��ɫ������Ч��
void app_display_func_rain(void)
{
	// static uint8_t list_descent_time_cnt[8] = {0}; 		// �½�ʱ�������
	// static uint8_t list_descent_speed[8] = {0};		// �½��ٶ�
	// static int8_t list_head_position[8] = {0};		// ��ͷλ��
	// static uint32_t list_color[8] = {0};			// ����ɫ
	// // static uint8_t list_head_brightness[8] = {0};	// ��ͷ����
	// static uint8_t list_len[8]	= {0};				// �г��� 3-5
	static uint8_t state = 0;
	static uint32_t temp_display_data[DISPLAY_MAX_LIST_NUM * DISPLAY_MAX_LINE_NUM] = { 0 };

	uint8_t temp_body_position = 0;
	uint8_t temp_head_position = 0;

	// ������ʼ������
	if (state == 0)
	{
		memset(temp_display_data, 0, sizeof(temp_display_data));
		memset(list_descent_speed, 0, sizeof(list_descent_speed));
		memset(list_descent_time_cnt, 0, sizeof(list_descent_time_cnt));

		for (uint8_t i = 0; i < 8; i++)
		{
			app_display_func_5_init_list(i);
		}
		state = 1;
	}
	else  // ��ʼ�½�
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			list_descent_time_cnt[i]++;
			if (list_descent_time_cnt[i] == list_descent_speed[i]) // �����½�ʱ�䣬�½�һ��
			{

				list_descent_time_cnt[i] = 0;
				list_head_position[i]++;


				// ���������
				for (uint8_t j = 0; j < 8; j++)
				{
					temp_display_data[(8 - i) * 8 - 1 - j] = 0;
				}

				// �����������
				// ��ͷ
				if (list_head_position[i] >= CANVAS_UPPER_LENGTH && list_head_position[i] < (CANVAS_UPPER_LENGTH + CANVAS_MIDDLE_LENGTH)) // ����ʾ��Χ��
					temp_display_data[(8 - i) * 8 - 1 - (list_head_position[i] - CANVAS_UPPER_LENGTH)] = app_set_brightness_level(list_color[i], 5);
				// ���� 
				for (uint8_t j = 0; j < (list_len[i] - 1); j++)
				{
					temp_body_position = list_head_position[i] - j - 1;
					if (temp_body_position >= CANVAS_UPPER_LENGTH && temp_body_position < (CANVAS_UPPER_LENGTH + CANVAS_MIDDLE_LENGTH)) // ����ʾ��Χ��
						temp_display_data[(8 - i) * 8 - 1 - (temp_body_position - CANVAS_UPPER_LENGTH)] = app_set_brightness_level(list_color[i], 5 - j - 1);
				}

				if (list_head_position[i] - list_len[i] > (CANVAS_UPPER_LENGTH + CANVAS_MIDDLE_LENGTH))
					app_display_func_5_init_list(i);
			}
		}
		memcpy(g_display_data, temp_display_data, sizeof(temp_display_data));
	}

}
