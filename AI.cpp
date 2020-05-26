#include"AI.h"

AI::AI():game_status(true),role(WHITE),count(1),head(EMPTY),end(EMPTY)
{
	for(int i = 0 ; i < BoardLength;i++)
		for (int j = 0; j < BoardLength; j++)
		{
			ai_score_board[i][j] = 0;
			hum_score_board[i][j] = 0;
			game_board[i][j] = 0;
			score_board[i][j] = -INF;
		}
	same_score_chess.push_back(best);
}

void AI::ReserveRole()
{
	if (role == BLACK)	role = WHITE;
	else role = BLACK;
}

//�ӿں���
void AI::UpdateBoard(int x, int y,Turns t)		//�������ӵ�
{
	game_board[x][y] = t;
	UpdateScore();
	if (Evaluate(BLACK) > FIVE || Evaluate(WHITE) > FIVE)
		game_status = false;
	//ReserveRole();
}

bool AI::GamingOrNot()
{
	return game_status;
}


void AI::ResetData()
{
	count = 1;
	head = EMPTY;
	end = EMPTY;
}

//�Ե����������
int AI::EvaluateGreedy(int x, int y,Turns color)
{
	int result = 0;
	//�� ��->  ��<-
	ResetData();
	for (int i = 1; i <= 4; i++)
	{
		if (y + i >= BoardLength || game_board[x][y + i] == opponent(color)) {
			head = BLOCK;
			break;
		}
		if (game_board[x][y + i] == EMPTY) {
			head = EMPTY;
			break;
		}
		if (game_board[x][y + i] == color)
			count++;
	}
	for (int i = 1; i <= 4; i++)
	{
		if (y - i < 0 || game_board[x][y - i] == opponent(color)) {
			end = BLOCK;
			break;
		}
		if (game_board[x][y - i] == EMPTY) {
			end = EMPTY;
			break;
		}
		if (game_board[x][y - i] == color)
			count++;
	}
	result += TurnToScore(count, head, end);

	//�� ���º���
	ResetData();
	for (int i = 1; i <= 4; i++)
	{
		if (x + i >= BoardLength || game_board[x + i][y] == opponent(color)) {
			head = BLOCK;
			break;
		}
		if (game_board[x + i][y] == EMPTY) {
			head = EMPTY;
			break;
		}
		if (game_board[x + i][y] == color)
			count++;
	}
	for (int i = 1; i <= 4; i++)
	{
		if (x - i < 0 || game_board[x - i][y] == opponent(color)) {
			end = BLOCK;
			break;
		}
		if (game_board[x - i][y] == EMPTY) {
			end = EMPTY;
			break;
		}
		if (game_board[x - i][y] == color)
			count++;
	}
	result += TurnToScore(count, head, end);

	// / ������������
	ResetData();
	for (int i = 1; i <= 4; i++)
	{
		if (x + i >= BoardLength || y - i < 0 || game_board[x + i][y - i] == opponent(color)) {
			head = BLOCK;
			break;
		}
		if (game_board[x + i][y - i] == EMPTY) {
			head = EMPTY;
			break;
		}
		if (game_board[x + i][y - i] == color)
			count++;
	}
	for (int i = 1; i <= 4; i++)
	{
		if (x - i < 0 || y + i >= BoardLength || game_board[x - i][y + i] == opponent(color)) {
			end = BLOCK;
			break;
		}
		if (game_board[x - i][y + i] == EMPTY) {
			end = EMPTY;
			break;
		}
		if (game_board[x - i][y + i] == color)
			count++;
	}
	result += TurnToScore(count, head, end);

	// \ ������������
	ResetData();
	for (int i = 1; i <= 4; i++)
	{
		if (x + i >= BoardLength || y + i >= BoardLength || game_board[x + i][y + i] == opponent(color)) {
			head = BLOCK;
			break;
		}
		if (game_board[x + i][y + i] == EMPTY) {
			head = EMPTY;
			break;
		}
		if (game_board[x + i][y + i] == color)
			count++;
	}
	for (int i = 1; i <= 4; i++)
	{
		if (x - i < 0 || y - i < 0 || game_board[x - i][y - i] == opponent(color)) {
			end = BLOCK;
			break;
		}
		if (game_board[x - i][y - i] == EMPTY) {
			end = EMPTY;
			break;
		}
		if (game_board[x - i][y - i] == color)
			count++;
	}
	result += TurnToScore(count, head, end);
	return result;
}

//�ѵ�����������ת��Ϊ����
int AI::TurnToScore(int cnt, Edge_Status h, Edge_Status e)
{
	if (cnt >= 5)
		return FIVE;

	if (cnt == 4)		//��if��ǰ�����еĿ����Զ��ŵ���ʣ�µĹ�Ϊһ��
	{
		if (h == EMPTY && e == EMPTY)//���߿� ����
			return FOUR;
		else if (h == BLOCK && e == BLOCK)//���߶� û��
			return NOTHREAT;
		else//ʣ�µ���Ȼ�ǳ���
			return BLOCKED_FOUR;
	}

	if (cnt == 3)
	{
		if (h == EMPTY && e == EMPTY)//���߿� ����
			return THREE;
		else if (h == BLOCK && e == BLOCK)//���߶� û��
			return NOTHREAT;
		else//ʣ�µ���Ȼ�ǳ���
			return BLOCKED_THREE;
	}
	if (cnt == 2)
	{
		if (h == EMPTY && e == EMPTY)//���߿� ���
			return TWO;
		else if (h == BLOCK && e == BLOCK)//���߶� û��
			return NOTHREAT;
		else//
			return BLOCKED_TWO;
	}
	if (cnt == 1)
	{
		if (h == EMPTY && e == EMPTY)//���߿� ����һ
			return NOTHREAT;
		else if (h == BLOCK && e == BLOCK)//���߶� û��
			return NOTHREAT;
		else//
			return BLOCKED_ONE;
	}
}

//̰���㷨�еĸ��º�������������º���
void AI::UpdateScoreGreedy()
{
	best.score = 0;
	for(int i = 0 ; i < BoardLength;i++)			//��������Ϊÿ����λ����
		for (int j = 0; j < BoardLength; j++)
		{
			if (game_board[i][j] == EMPTY)//��λ����
			{
				score_board[i][j] = EvaluateGreedy(i, j, BLACK) + EvaluateGreedy(i, j, WHITE);

				if (score_board[i][j] > best.score)
				{
					best.score = score_board[i][j];
					best.x = i;
					best.y = j;
					same_score_chess.clear();
					same_score_chess.push_back(best);
				}
				if (score_board[i][j] == best.score)
				{
					best.score = score_board[i][j];
					best.x = i;
					best.y = j;
					same_score_chess.push_back(best);
				}
				
				int human = EvaluateGreedy(i, j, WHITE);
				int bot = EvaluateGreedy(i, j, BLACK);
			}
		}
}

//minmax�㷨�еĸ��º���
/*�ҵĸ��²��ԣ�1.��ͨ��gen�����Կ����ӵ���й�ֵ����ѡǰ10���Ÿ���
	2.����ÿ������С�Ԥ���塱
	3.�ڷ�����������minimax��Ԥ���������ӷ������й�ֵ������һ�㣩
		i)�������ӷ���������ߵ㣬����ߵ���Ϊ��
		ii)�������ӷ���������ߵ㣬��������������ӵ�vector��
	4.ɾ��������
*/
void AI::UpdateScore()
{
	best.score = -INF;
	for (int i = 0; i < BoardLength; i++)
		for (int j = 0; j < BoardLength; j++)
		{
			score_board[i][j] = -INF;
		}

	std::vector<Chess> points;
	gen(points, BLACK);
	for (int i = 0; i < 10; i++)
	{
		game_board[points[i].x][points[i].y] = BLACK;
		score_board[points[i].x][points[i].y] = minimax(DEPTH - 1, -INF, INF, false);//
		if (score_board[points[i].x][points[i].y] > best.score)
		{
			best.score = score_board[points[i].x][points[i].y];
			best.x = points[i].x;
			best.y = points[i].y;
			same_score_chess.clear();
			same_score_chess.push_back(best);
		}
		if (score_board[points[i].x][points[i].y] == best.score)
		{
			best.score = score_board[points[i].x][points[i].y];
			best.x = points[i].x;
			best.y = points[i].y;
			same_score_chess.push_back(best);
		}
		game_board[points[i].x][points[i].y] = EMPTY;
	}

}

//�����Ӵ��������е���õ��������
Chess& AI::BestChess()
{
	srand((unsigned)time(0));
	int i = rand() % same_score_chess.size();
	game_board[same_score_chess[i].x][same_score_chess[i].y] = BLACK;
	if (Evaluate(BLACK) > FIVE || Evaluate(WHITE) > FIVE)
		game_status = false;
	return same_score_chess[i];
}

//alpha���壺�������������/���ƺ������棩���-������    beta���壺�������������/���ư������棩��С-������   
//����ʱalpha �� beta��ֵ���ݶ���
//max��ȡmax������_��_������ȡֵ��max����  min��ͬ��
//����max���з���alpha����beta��������������棩���ڣ���������棩����ô������һ�㣨�����minȡ��С�����϶�����ư������棬��������壬����˵����֮�����Ч����֦
//����min���з���alpha����beta���������alpha�ɰ��崫�ݹ����������alpha�����º����betaȷ����������alpha��֮ǰ����ȷ�������������ⲽ������û�к�����һ���ߣ�����Ϊ��������󻯿϶������£����Լ�֦
//���ô�Ԥ�����壬�㲻���������
/*�ҵ�minimax���²��ԣ��ݹ飩
	0.�жϲ����Ƿ�ͷ����ͷ�󷵻ص�ǰ�����µķ���
	1.gen��Ԥ����
	2.
	
*/
int AI::minimax(int depth, int alpha, int beta, bool maxmizingPlayer)
{
	if (depth == 0)
		return Evaluate(BLACK);//����СĬ������ż���㣬black�������

	std::vector<Chess> points;

	if (maxmizingPlayer)
	{
		int maxEval = -1000000;			//����һ��������ֵ��֤����ȡ��	  Ϊʲô�� ���������ж�������alpha����betaʱֹͣ����������и���ѡ��
		gen(points, BLACK);
		for (int i = 0; i < 10; i++)
		{
			game_board[points[i].x][points[i].y] = BLACK;
			int eval =  minimax(depth - 1, alpha, beta, false);
			game_board[points[i].x][points[i].y] = EMPTY;
			if (eval != 0) {
				maxEval = maxEval > eval ? maxEval : eval;						//����ֵ
				alpha = alpha > eval ? alpha : eval;							//���ݵ�ֵ���������жϼ�֦
			}
			if (beta <= alpha)
				break;
		}
		return maxEval;
	}
	else{
		int minEval = 1000000;
		gen(points, WHITE);
		for (int i = 0; i < 10; i++)
		{
			game_board[points[i].x][points[i].y] = WHITE;
			int eval = minimax(depth - 1, alpha, beta, true);
			game_board[points[i].x][points[i].y] = EMPTY;
			if (eval != 0) {
				minEval = minEval < eval ? minEval : eval;
				beta = beta < eval ? beta : eval;
			}
			if (beta <= alpha)
				break;
		}
		return minEval;
	}
}

//�ж�������Χ���������Ƿ�������
bool AI::HasNeighbour(int x, int y)
{
	int neighbour = 0;
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			if (y + j >= BoardLength || y + j < 0 || x + i >= BoardLength || x + i < 0 || game_board[x + i][y + j] == EMPTY)
				continue;
			else if (i == 0 && j == 0)	continue;
			else if (game_board[x + i][y + j] == 0) continue;
			else neighbour++;
		}
	}

	return neighbour != 0;
}

//��������Χ�ĵ���з�ֵ����󷵻ظ�minimax�Լӿ��֦�ٶ�
void AI::gen(std::vector<Chess>& v, Turns t)
{
	Chess c;
	for (int i = 0; i < BoardLength; i++)
	{
		for (int j = 0; j < BoardLength; j++)
		{
			if (game_board[i][j] == EMPTY && HasNeighbour(i, j))
			{
				c.score = EvaluateGreedy(i, j, t)+EvaluateGreedy(i,j,opponent(t));			//�����ӷ���
				c.x = i;
				c.y = j;
				v.push_back(c);
			}
		}
	}
	sort(v);
}

//minimax�е�ȫ�����ֺ���
//�жϸ�����ɫ�����ӵ������ж��٣������������ӵ㣩
int AI::Evaluate(Turns t)
{
	int score = 0;
	for (int i = 0; i < BoardLength; i++)
		for (int j = 0; j < BoardLength; j++)
		{
			if (game_board[i][j] == t)
				score += EvaluateGreedy(i, j, t);
			else if (game_board[i][j] == opponent(t))
				score -= EvaluateGreedy(i, j, opponent(t));
		}
	return score;
}

//����gen�����е�����
void AI::sort(std::vector<Chess>& v)			//����
{
	for (int i = 0; i < v.size() - 1; i++)
	{
		for (int j = 0; j < v.size() - i - 1; j++)
		if (v[j].score < v[j + 1].score) {
			Chess t = v[j + 1];
			v[j + 1] = v[j];
			v[j] = t;
		}
	}
}

//5.20 �����˼�֦˳���ֹ����
//������inf��С��ֹ������