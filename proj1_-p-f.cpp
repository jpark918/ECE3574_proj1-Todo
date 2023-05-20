if (arguments[1] == "-f") { //  ./todo [-f file] [-p priority] command 
			std::ifstream input_file(argv[2]);
			if (arguments[3] == "-p" && arguments[5] == "add") { //(-p priority only for add, also more text can be added for task description)
				for (size_t i = 0; i < arguments[4].size(); i++) {
					char character = arguments[4][i];
					if (character < 48 || character > 57) {
						cout << "not a number for -p " << endl;
						return EXIT_FAILURE;
					}
				}
				int num = stoi(arguments[4]);
				if (num < 1 || num > 10) { //Check -p correct value
					cout << "incorrect -p value" << endl;
					return EXIT_FAILURE;
				}
				//This code checks for correct -p values

				if (!input_file) {  //HELP assume that the user enters in .txt file?
					std::ofstream out_file(argv[2]); //writing to a new empty file
					out_file << "1:[ ][" << arguments[4] << "]";
					for (int i = 6; i < argc; i++) {
						if (arguments[i][0] == '"') {	//if the description has a "
							arguments[i] = arguments[i].substr(1);
							out_file << " " << arguments[i];
						}
						if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
							arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
							out_file << " " << arguments[i];
						}
						else {		//description does not have "
							out_file << " " << arguments[i];
						}
					}
					out_file.close();
					return EXIT_SUCCESS;
				}
				else { //the file name exists in directory
					vector<string> uhaul;
					int i = 0;
					string line;
					while (getline(input_file, line)) {
						uhaul.emplace_back(line);
						i++;
					}
					std::ofstream out_filedel; //writing to non-empty file
					out_filedel.open(argv[2], std::ofstream::out | std::ofstream::trunc); //delete content in file
					out_filedel.close();
					std::ofstream out_file(argv[2]); //re-open? now empty file
					bool added = false;
					int newprio = stoi(arguments[4]);
					int priorityval = 0;
					int listorder = 1;
					for (size_t i = 0; i < uhaul.size(); i++) { //shoving in lines into the txt file	
						if (uhaul[i][7] == 48) { //if the priority value is 10
							priorityval = 10;
						}
						else {
							priorityval = uhaul[i][6] - '0'; //single value (0 - 9)
						}
						if (priorityval < newprio) {
							//change the list order as well!!
							char change = '0' + listorder;
							uhaul[i][0] = change;
							listorder++;
							out_file << uhaul[i] << endl;
						}
						else if (priorityval == newprio) {
							//change the list order as well!
							char change = '0' + listorder;
							uhaul[i][0] = change;
							listorder++;
							out_file << uhaul[i] << endl; //HELP add in the list priority duplicate first?
							//add in the new command line next			
							if (i < uhaul.size() - 1) {
								int priorityval2 = 0;
								if (uhaul[i + 1][7] == 48) {
									priorityval2 = 10;
								}
								else {
									priorityval2 = uhaul[i + 1][6] - '0';
								}
								if (added == false && priorityval2 != priorityval) {
									char change2 = '0' + listorder;
									out_file << change2 << ":" << "[ ][" << arguments[4] << "]";
									for (int i = 6; i < argc; i++) {
										if (arguments[i][0] == '"') {	//if the description has a "
											arguments[i] = arguments[i].substr(1);
											out_file << " " << arguments[i];
										}
										if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
											arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
											out_file << " " << arguments[i];
										}
										else {		//description does not have "
											out_file << " " << arguments[i];
										}
									}
									listorder++;
									added = true;
								}
							}
						}
						else if (priorityval > newprio) {
							//add in the new command line first
							if (added == false) {
								char change2 = '0' + listorder;
								out_file << change2 << ":" << "[ ][" << arguments[4] << "]";
								for (int i = 6; i < argc; i++) {
									if (arguments[i][0] == '"') {	//if the description has a "
										arguments[i] = arguments[i].substr(1);
										out_file << " " << arguments[i];
									}
									if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
										arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
										out_file << " " << arguments[i];
									}
									else {		//description does not have "
										out_file << " " << arguments[i];
									}
								}
								out_file << endl;
								listorder++;
								added = true;
							}
							//change the list order as well!
							char change = '0' + listorder;
							uhaul[i][0] = change;
							listorder++;
							out_file << uhaul[i] << endl;
						}
						if (i == uhaul.size() - 1 && added == false) { //if I am on the last line aka the command line is the last line in the list to be added
							char change2 = '0' + listorder;
							out_file << change2 << ":" << "[ ][" << arguments[4] << "]";
							for (int i = 6; i < argc; i++) {
								if (arguments[i][0] == '"') {	//if the description has a "
									arguments[i] = arguments[i].substr(1);
									out_file << " " << arguments[i];
								}
								if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
									arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
									out_file << " " << arguments[i];
								}
								else {		//description does not have "
									out_file << " " << arguments[i];
								}
							}
							listorder++;
						}
					} 
					out_file.close();
					return EXIT_SUCCESS;
				}
			}
			else if (arguments[3] == "add") { //no "-p" but has "-f"
				if (!input_file) {  //HELP assume that the user enters in .txt file?
					std::ofstream out_file(argv[2]); //writing to a new empty file
					out_file << "1:[ ][5]";
					for (int i = 4; i < argc; i++) {
						if (arguments[i][0] == '"') {	//if the description has a "
							arguments[i] = arguments[i].substr(1);
							out_file << " " << arguments[i];
						}
						if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
							arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
							out_file << " " << arguments[i];
						}
						else {		//description does not have "
							out_file << " " << arguments[i];
						}
					}
					out_file.close();
					return EXIT_SUCCESS;
				}
				else { //the file name exists in directory
					vector<string> uhaul;
					int i = 0;
					string line;
					while (getline(input_file, line)) {
						uhaul.emplace_back(line);
						i++;
					}
					std::ofstream out_filedel; //writing to non-empty file
					out_filedel.open(argv[2], std::ofstream::out | std::ofstream::trunc); //delete content in file
					out_filedel.close();
					std::ofstream out_file(argv[2]); //re-open? now empty file
					bool added = false;
					int priorityval = 0;
					int listorder = 1;
					for (size_t i = 0; i < uhaul.size(); i++) { //shoving in lines into the txt file	
						if (uhaul[i][7] == 48) { //if the priority value is 10
							priorityval = 10;
						}
						else {
							priorityval = uhaul[i][6] - '0'; //single value (0 - 9)
						}
						if (priorityval < 5) {
							//change the list order as well!!
							char change = '0' + listorder;
							uhaul[i][0] = change;
							listorder++;
							out_file << uhaul[i] << endl;
						}
						else if (priorityval == 5) {
							//change the list order as well!
							char change = '0' + listorder;
							uhaul[i][0] = change;
							listorder++;
							out_file << uhaul[i] << endl; //HELP add in the list priority duplicate first?
							//add in the new command line next
							if (i < uhaul.size() - 1) {
								int priorityval2 = 0;
								if (uhaul[i + 1][7] == 48) {
									priorityval2 = 10;
								}
								else {
									priorityval2 = uhaul[i + 1][6] - '0';
								}
								if (added == false && priorityval2 != priorityval) {
									char change2 = '0' + listorder;
									out_file << change2 << ":" << "[ ][5]";
									for (int i = 4; i < argc; i++) {
										if (arguments[i][0] == '"') {	//if the description has a "
											arguments[i] = arguments[i].substr(1);
											out_file << " " << arguments[i];
										}
										if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
											arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
											out_file << " " << arguments[i];
										}
										else {		//description does not have "
											out_file << " " << arguments[i];
										}
									}
									out_file << endl;
									listorder++;
									added = true;
								}
							}
						}
						else if (priorityval > 5) {
							//add in the new command line first
							if (added == false) {
								char change2 = '0' + listorder;
								out_file << change2 << ":" << "[ ][5]";
								for (int i = 4; i < argc; i++) {
									if (arguments[i][0] == '"') {	//if the description has a "
										arguments[i] = arguments[i].substr(1);
										out_file << " " << arguments[i];
									}
									if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
										arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
										out_file << " " << arguments[i];
									}
									else {		//description does not have "
										out_file << " " << arguments[i];
									}
								}
								out_file << endl;
								listorder++;
								added = true;
							}
							//change the list order as well!
							char change = '0' + listorder;
							uhaul[i][0] = change;
							listorder++;
							out_file << uhaul[i] << endl;
						}
						if (i == uhaul.size() - 1 && added == false) { //if I am on the last line aka the command line is the last line in the list to be added
							char change2 = '0' + listorder;
							out_file << change2 << ":" << "[ ][5]";
							for (int i = 4; i < argc; i++) {
								if (arguments[i][0] == '"') {	//if the description has a "
									arguments[i] = arguments[i].substr(1);
									out_file << " " << arguments[i];
								}
								if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
									arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
									out_file << " " << arguments[i];
								}
								else {		//description does not have "
									out_file << " " << arguments[i];
								}
							}
							listorder++;
						}
					}
					out_file.close();
					return EXIT_SUCCESS;
				}
			}
			else { //no "-p" and no add (list and do not allowed because argc >= 6)
				return EXIT_FAILURE;
			}
		}
		else if (arguments[1] == "-p" && arguments[3] == "add") { // no -f but has -p							Note that " " count as 1 argv

			for (size_t i = 0; i < arguments[2].size(); i++) {
				char character = arguments[2][i];
				if (character < 48 || character > 57) {
					cout << "not a number for -p " << endl;
					return EXIT_FAILURE;
				}
			}
			int num = stoi(arguments[2]);
			if (num < 1 || num > 10) { //Check -p correct value
				cout << "incorrect -p value" << endl;
				return EXIT_FAILURE;
			}
			//This code checks for correct -p values

			std::ifstream input_file("todo.txt");
			if (!input_file) {  //HELP assume that the user enters in .txt file?
				std::ofstream out_file("todo.txt"); //writing to a new empty file
				out_file << "1:[ ][" << arguments[2] << "]";
				for (int i = 4; i < argc; i++) {
					if (arguments[i][0] == '"') {	//if the description has a "
						arguments[i] = arguments[i].substr(1);
						out_file << " " << arguments[i];
					}
					if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
						arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
						out_file << " " << arguments[i];
					}
					else {		//description does not have "
						out_file << " " << arguments[i];
					}
				}
				out_file.close();
				return EXIT_SUCCESS;
			}
			else { //the file name exists in directory
				vector<string> uhaul;
				int i = 0;
				string line;
				while (getline(input_file, line)) {
					uhaul.emplace_back(line);
					i++;
				}
				std::ofstream out_filedel; //writing to non-empty file
				out_filedel.open("todo.txt", std::ofstream::out | std::ofstream::trunc); //delete content in file
				out_filedel.close();
				std::ofstream out_file("todo.txt"); //re-open? now empty file
				bool added = false;
				int newprio = stoi(arguments[2]);
				int priorityval = 0;
				int listorder = 1;
				for (size_t i = 0; i < uhaul.size(); i++) { //shoving in lines into the txt file	
					if (uhaul[i][7] == 48) { //if the priority value is 10
						priorityval = 10;
					}
					else {
						priorityval = uhaul[i][6] - '0'; //single value (0 - 9)
					}
					if (priorityval < newprio) {
						//change the list order as well!!
						char change = '0' + listorder;
						uhaul[i][0] = change;
						listorder++;
						out_file << uhaul[i] << endl;
					}
					else if (priorityval == newprio) {
						//change the list order as well!
						char change = '0' + listorder;
						uhaul[i][0] = change;
						listorder++;
						out_file << uhaul[i] << endl; //HELP add in the list priority duplicate first?
						//add in the new command line next
						if (i < uhaul.size() - 1) {
							int priorityval2 = 0;
							if (uhaul[i + 1][7] == 48) {
								priorityval2 = 10;
							}
							else {
								priorityval2 = uhaul[i + 1][6] - '0';
							}
							if (added == false && priorityval2 != priorityval) {
								char change2 = '0' + listorder;
								out_file << change2 << ":" << "[ ][" << arguments[2] << "]";
								for (int i = 4; i < argc; i++) {
									if (arguments[i][0] == '"') {	//if the description has a "
										arguments[i] = arguments[i].substr(1);
										out_file << " " << arguments[i];
									}
									if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
										arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
										out_file << " " << arguments[i];
									}
									else {		//description does not have "
										out_file << " " << arguments[i];
									}
								}
								out_file << endl;
								listorder++;
								added = true;
							}
						}
					}
					else if (priorityval > newprio) {
						//add in the new command line first
						if (added == false) {
							char change2 = '0' + listorder;
							out_file << change2 << ":" << "[ ][" << arguments[2] << "]";
							for (int i = 4; i < argc; i++) {
								if (arguments[i][0] == '"') {	//if the description has a "
									arguments[i] = arguments[i].substr(1);
									out_file << " " << arguments[i];
								}
								if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
									arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
									out_file << " " << arguments[i];
								}
								else {		//description does not have "
									out_file << " " << arguments[i];
								}
							}
							out_file << endl;
							listorder++;
							added = true;
						}
						//change the list order as well!
						char change = '0' + listorder;
						uhaul[i][0] = change;
						listorder++;
						out_file << uhaul[i] << endl;
					}
					if (i == uhaul.size() - 1 && added == false) { //if I am on the last line aka the command line is the last line in the list to be added
						char change2 = '0' + listorder;
						out_file << change2 << ":" << "[ ][" << arguments[2] << "]";
						for (int i = 4; i < argc; i++) {
							if (arguments[i][0] == '"') {	//if the description has a "
								arguments[i] = arguments[i].substr(1);
								out_file << " " << arguments[i];
							}
							if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
								arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
								out_file << " " << arguments[i];
							}
							else {		//description does not have "
								out_file << " " << arguments[i];
							}
						}
						listorder++;
					}
				}
				out_file.close();
				return EXIT_SUCCESS;
			}
		}
		else if (arguments[1] == "add") { //when there is no -p and no -f
			std::ifstream input_file("todo.txt");
			if (!input_file) {  //HELP assume that the user enters in .txt file?
				std::ofstream out_file("todo.txt"); //writing to a new empty file
				out_file << "1:[ ][5]";
				for (int i = 2; i < argc; i++) {
					if (arguments[i][0] == '"') {	//if the description has a "
						arguments[i] = arguments[i].substr(1);
						out_file << " " << arguments[i];
					}
					if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
						arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
						out_file << " " << arguments[i];
					}
					else {		//description does not have "
						out_file << " " << arguments[i];
					}
				}
				out_file.close();
				return EXIT_SUCCESS;
			}
			else { //the file name exists in directory
				vector<string> uhaul;
				int i = 0;
				string line;
				while (getline(input_file, line)) {
					uhaul.emplace_back(line);
					i++;
				}
				std::ofstream out_filedel; //writing to non-empty file
				out_filedel.open("todo.txt", std::ofstream::out | std::ofstream::trunc); //delete content in file
				out_filedel.close();
				std::ofstream out_file("todo.txt"); //re-open? now empty file
				bool added = false;
				int priorityval = 0;
				int listorder = 1;
				for (size_t i = 0; i < uhaul.size(); i++) { //shoving in lines into the txt file	
					if (uhaul[i][7] == 48) { //if the priority value is 10
						priorityval = 10;
					}
					else {
						priorityval = uhaul[i][6] - '0'; //single value (0 - 9)
					}
					if (priorityval < 5) {
						//change the list order as well!!
						char change = '0' + listorder;
						uhaul[i][0] = change;
						listorder++;
						out_file << uhaul[i] << endl;
					}
					else if (priorityval == 5) {
						//change the list order as well!
						char change = '0' + listorder;
						uhaul[i][0] = change;
						listorder++;
						out_file << uhaul[i] << endl; //HELP add in the list priority duplicate first?
						//add in the new command line next
						if (i < uhaul.size() - 1) {
							int priorityval2 = 0;
							if (uhaul[i + 1][7] == 48) {
								priorityval2 = 10;
							}
							else {
								priorityval2 = uhaul[i + 1][6] - '0';
							}
							if (added == false && priorityval2 != priorityval) {
								char change2 = '0' + listorder;
								out_file << change2 << ":" << "[ ][5]";
								for (int i = 2; i < argc; i++) {
									if (arguments[i][0] == '"') {	//if the description has a "
										arguments[i] = arguments[i].substr(1);
										out_file << " " << arguments[i];
									}
									if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
										arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
										out_file << " " << arguments[i];
									}
									else {		//description does not have "
										out_file << " " << arguments[i];
									}
								}
								out_file << endl;
								listorder++;
								added = true;
							}
						}
					}
					else if (priorityval > 5) {
						//add in the new command line first
						if (added == false) {
							char change2 = '0' + listorder;
							out_file << change2 << ":" << "[ ][5]";
							for (int i = 2; i < argc; i++) {
								if (arguments[i][0] == '"') {	//if the description has a "
									arguments[i] = arguments[i].substr(1);
									out_file << " " << arguments[i];
								}
								if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
									arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
									out_file << " " << arguments[i];
								}
								else {		//description does not have "
									out_file << " " << arguments[i];
								}
							}
							out_file << endl;
							listorder++;
							added = true;
						}
						//change the list order as well!
						char change = '0' + listorder;
						uhaul[i][0] = change;
						listorder++;
						out_file << uhaul[i] << endl;
					}
					if (i == uhaul.size() - 1 && added == false) { //if I am on the last line aka the command line is the last line in the list to be added
						char change2 = '0' + listorder;
						out_file << change2 << ":" << "[ ][5]";
						for (int i = 2; i < argc; i++) {
							if (arguments[i][0] == '"') {	//if the description has a "
								arguments[i] = arguments[i].substr(1);
								out_file << " " << arguments[i];
							}
							if (arguments[i][arguments[i].size() - 1] == '"') {	//if the description has a "
								arguments[i] = arguments[i].substr(0, arguments[i].size() - 2);
								out_file << " " << arguments[i];
							}
							else {		//description does not have "
								out_file << " " << arguments[i];
							}
						}
						listorder++;
					}
				}
				out_file.close();
				return EXIT_SUCCESS;
			}
		}
		else {
			cout << "invalid command(s)" << endl;
			return EXIT_FAILURE;
		}