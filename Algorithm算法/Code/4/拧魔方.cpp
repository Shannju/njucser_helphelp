void move(char side, bool cw) {
		/* TODO:
		move one key step:
		let one side rotate clockwise or counterclockwise by 90°
		params:
		side = 'F' | 'B' | 'L' | 'R' | 'U' | 'D' |
		cw = true => clockwise | false => counterclockwise
		*/
		vector<vector<char>> tempside(n, vector<char>(n, 'w'));
		vector<vector<char>> f = cube[0];
		vector<vector<char>> b = cube[1];
		vector<vector<char>> l = cube[2];
		vector<vector<char>> r = cube[3];
		vector<vector<char>> u = cube[4];
		vector<vector<char>> d = cube[5];
		// vector<char> tmp=(n, 'w');
		if(side == 'F')
		{
			if (cw == true)
			{
				//cout << "flag1" << endl;
				for (int i = 0; i != n; ++i)
				{
					for (int j = 0; j != n; ++j)
					{
						tempside[j][n - i - 1] = f[i][j];
					}
				}
				f = tempside;
				vector<char> tmp= u[n - 1];
				for (int i = 0; i != n; ++i)
					u[n - 1][n - i - 1] = l[i][n - 1];
				for (int i = 0; i != n; ++i)
					l[i][n - 1] = d[0][i];
				for (int i = 0; i != n; ++i)
					d[0][n - i - 1] = r[i][0];
				for (int i = 0; i != n; ++i)
					r[i][0] = tmp[i];
				//cout << "flag2" << endl;
			}
			else
			{
				//cout << "flag3" << endl;
				for (int i = 0; i != n; ++i)
				{
					for (int j = 0; j != n; ++j)
					{
						tempside[n - j - 1][i] = f[i][j];
					}
				}
				f = tempside;
				vector<char> tmp= u[n - 1];
				for (int i = 0; i != n; ++i)
					u[n - 1][i] = r[i][0];
				for (int i = 0; i != n; ++i)
					r[n - i - 1][0] = d[0][i];
				for (int i = 0; i != n; ++i)
					d[0][i] = l[i][n - 1];
				for (int i = 0; i != n; ++i)
					l[n - i - 1][n - 1] = tmp[i];
				//cout << "flag4" << endl;
			}
		}
		else if(side == 'B')
		{
			if (cw == true)
			{
				//cout << "flag5" << endl;
				for (int i = 0; i != n; ++i)
				{
					for (int j = 0; j != n; ++j)
					{
						tempside[j][n - i - 1] = b[i][j];
					}
				}
				b = tempside;
				vector<char> tmp= u[0];
				for (int i = 0; i != n; ++i)
					u[0][i] = r[i][n - 1];
				for (int i = 0; i != n; ++i)
					r[n - i -1][n - 1] = d[n - 1][i];
				for (int i = 0; i != n; ++i)
					d[n - 1][i] = l[i][0];
				for (int i = 0; i != n; ++i)
					l[n - i - 1][0] = tmp[i];
				//cout << "flag6" << endl;
			}
			else
			{
				//cout << "flag7" << endl;
				for (int i = 0; i != n; ++i)
				{
					for (int j = 0; j != n; ++j)
					{
						tempside[n - j - 1][i] = b[i][j];
					}
				}
				b = tempside;
				vector<char> tmp= u[0];
				for (int i = 0; i != n; ++i)
					u[0][n - i - 1] = l[i][0];
				for (int i = 0; i != n; ++i)
					l[i][0] = d[n - 1][i];
				for (int i = 0; i != n; ++i)
					d[n - 1][n - i - 1] = r[i][n - 1];
				for (int i = 0; i != n; ++i)
					r[i][n - 1] = tmp[i];
				//cout << "flag8" << endl;
			}
		}
		else if(side == 'L')
		{
			if (cw == true)
			{
				//cout << "flag9" << endl;
				for (int i = 0; i != n; ++i)
				{
					for (int j = 0; j != n; ++j)
					{
						tempside[j][n - i - 1] = l[i][j];
					}
				}
				l = tempside;
				for(int i = 0; i != n; ++i)
					tmp[i] = u[i][0];
				for (int i = 0; i != n; ++i)
					u[n - i - 1][0] = b[i][n - 1];
				for (int i = 0; i != n; ++i)
					b[n - i - 1][n - 1] = d[i][0];
				for (int i = 0; i != n; ++i)
					d[i][0] = f[i][0];
				for (int i = 0; i != n; ++i)
					f[i][0] = tmp[i];
				//cout << "flag10" << endl;
			}
			else
			{
				//cout << "flag11" << endl;
				for (int i = 0; i != n; ++i)
				{
					for (int j = 0; j != n; ++j)
					{
						tempside[n- j - 1][i] = l[i][j];
					}
				}
				l = tempside;
				for(int i = 0; i != n; ++i)
					tmp[i] = u[i][0];
				for (int i = 0; i != n; ++i)
					u[i][0] = f[i][0];
				for (int i = 0; i != n; ++i)
					f[i][0] = d[i][0];
				for (int i = 0; i != n; ++i)
					d[n - i - 1][0] = b[i][n - 1];
				for (int i = 0; i != n; ++i)
					b[n - i - 1][n - 1] = tmp[i];
				//cout << "flag12" << endl;
			}
		}
		else if(side == 'R')
		{
			if (cw == true)
			{
				//cout << "flag13" << endl;
				for (int i = 0; i != n; ++i)
				{
					for (int j = 0; j != n; ++j)
					{
						tempside[j][n - i - 1] = r[i][j];
					}
				}
				r = tempside;
				for(int i = 0; i != n; ++i)
					tmp[i] = u[i][n - 1];
				for (int i = 0; i != n; ++i)
					u[i][n - 1] = f[i][n - 1];
				for (int i = 0; i != n; ++i)
					f[i][n - 1] = d[i][n - 1];
				for (int i = 0; i != n; ++i)
					d[n - i - 1][n - 1] = b[i][0];
				for (int i = 0; i != n; ++i)
					b[n - i - 1][0] = tmp[i];
				//cout << "flag14" << endl;
			}
			else
			{
				//cout << "flag15" << endl;
				for (int i = 0; i != n; ++i)
				{
					for (int j = 0; j != n; ++j)
					{
						tempside[n - j - 1][i] = r[i][j];
					}
				}
				r = tempside;
				for(int i = 0; i != n; ++i)
					tmp[i] = u[i][n - 1];
				for (int i = 0; i != n; ++i)
					u[n - i - 1][n - 1] = b[i][0];
				for (int i = 0; i != n; ++i)
					b[n - i - 1][0] = d[i][n - 1];
				for (int i = 0; i != n; ++i)
					d[i][n - 1] = f[i][n - 1];
				for (int i = 0; i != n; ++i)
					f[i][n - 1] = tmp[i];
				//cout << "flag16" << endl;
			}
		}
		else if(side == 'U')
		{
			if (cw == true)
			{
				//cout << "flag17" << endl;
				for (int i = 0; i != n; ++i)
				{
					for (int j = 0; j != n; ++j)
					{
						tempside[j][n - i - 1] = u[i][j];
					}
				}
				u = tempside;
				vector<char> tmp= f[0];
				for (int i = 0; i != n; ++i)
					f[0][i] = r[0][i];
				for (int i = 0; i != n; ++i)
					r[0][i] = b[0][i];
				for (int i = 0; i != n; ++i)
					b[0][i] = l[0][i];
				for (int i = 0; i != n; ++i)
					l[0][i] = tmp[i];
				//cout << "flag18" << endl;
			}
			else
			{
				//cout << "flag19" << endl;
				for (int i = 0; i != n; ++i)
				{
					for (int j = 0; j != n; ++j)
					{
						tempside[n - j - 1][i] = u[i][j];
					}
				}
				u = tempside;
				vector<char> tmp= f[0];
				for (int i = 0; i != n; ++i)
					f[0][i] = l[0][i];
				for (int i = 0; i != n; ++i)
					l[0][i] = b[0][i];
				for (int i = 0; i != n; ++i)
					b[0][i] = r[0][i];
				for (int i = 0; i != n; ++i)
					r[0][i] = tmp[i];
				//cout << "flag20" << endl;
			}
		}
		else if(side == 'D')
		{
			if (cw == true)
			{
				//cout << "flag21" << endl;
				for (int i = 0; i != n; ++i)
				{
					for (int j = 0; j != n; ++j)
					{
						tempside[j][n - i - 1] = d[i][j];
					}
				}
				d = tempside;
				vector<char> tmp= f[n - 1];
				for (int i = 0; i != n; ++i)
					f[n - 1][i] = l[n - 1][i];
				for (int i = 0; i != n; ++i)
					l[n - 1][i] = b[n - 1][i];
				for (int i = 0; i != n; ++i)
					b[n - 1][i] = r[n - 1][i];
				for (int i = 0; i != n; ++i)
					r[n - 1][i] = tmp[i];
				//cout << "flag22" << endl;
			}
			else
			{
				//cout << "flag23" << endl;
				for (int i = 0; i != n; ++i)
				{
					for (int j = 0; j != n; ++j)
					{
						tempside[n - j - 1][i] = d[i][j];
					}
				}
				d = tempside;
				vector<char> tmp= f[n - 1];
				for (int i = 0; i != n; ++i)
					f[n - 1][i] = r[n - 1][i];
				for (int i = 0; i != n; ++i)
					r[n - 1][i] = b[n - 1][i];
				for (int i = 0; i != n; ++i)
					b[n - 1][i] = l[n - 1][i];
				for (int i = 0; i != n; ++i)
					l[n - 1][i] = tmp[i];
				//cout << "flag24" << endl;
			}
		}
		cube[0] = f;
		cube[1] = b;
		cube[2] = l;
		cube[3] = r;
		cube[4] = u;
		cube[5] = d;
		//printcube();
	}