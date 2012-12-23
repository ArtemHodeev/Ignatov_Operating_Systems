#pragma once
#include <time.h>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vcclr.h>

namespace эмулятор {
	using namespace System::Runtime::InteropServices;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	//
	//
	struct elem	
	{
		wchar_t index_button;
		int index_simbol; 	
		time_t start;
	};
	elem click_button;
	int current_position_cursor;
	int symbol_new_or_replaced;
	int button_registr;
	

	//
	int i_flag_registr = 0; //если i_flag_registr = 0, то регистр ввода в режиме "Аа"
	//						//если i_flag_registr = 1, то регистр ввода в режиме "АА"
	//						//если i_flag_registr = 2, то регистр ввода в режиме "123"
	//						//если i_flag_registr = 3, то регистр ввода в режиме "аа"
			
	//int current_position_cursor; 

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  abc2;
	private: System::Windows::Forms::Button^  def3;
	private: System::Windows::Forms::Button^  dell_one;
	private: System::Windows::Forms::Button^  dell_all;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  text_form;
	private: System::Windows::Forms::Button^  ghi4;
	private: System::Windows::Forms::Button^  jkl5;
	private: System::Windows::Forms::Button^  mno6;
	private: System::Windows::Forms::Button^  _0;

	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  pqrs7;
	private: System::Windows::Forms::Button^  tuv8;
	private: System::Windows::Forms::Button^  wxyz9;
	private: System::Windows::Forms::Button^  registrs;
	private: System::Windows::Forms::Button^  right;
	private: System::Windows::Forms::Button^  left;
   
	//
	//добавление нажатого символа в поле ввода с необходимым регистром 
	//
	void add_simbol_in_textform(String^ button_text, int length_button_text, int &button_registr)
	{
				 wchar_t simbol_to_add, digit_to_add;
				 digit_to_add = button_text[length_button_text - 1];
				 
				 current_position_cursor = this->text_form->SelectionStart;
				 time_t start;
				 
				 start = time(NULL);
				 bool flag = change_registr_if_point_and_space(this->text_form->Text, current_position_cursor);
				 if (flag == true)
				 {
					 button_registr = 0;
					 to_state_label_in_textform(button_registr);
					 symbol_new_or_replaced = -1;
				 }

				 if (symbol_new_or_replaced == -1)														//если регистр не "Аа" 
				 {
				 }
				 else if (((difftime(start, click_button.start) > 1) && (button_registr == 0))			//если регистр "Аа" был установлен, 
					  || ((click_button.index_button != digit_to_add) && (button_registr == 0)))		//и некоторая кнопка уже была нажата 
				 {
						 button_registr = 3;															//меняем регистр на "аа"
						 to_state_label_in_textform(button_registr);
				 }
				 if (this->text_form->Text->Length >= 80)												// если пользователь вводит 81 символ, 
				 {																						// система игнорирует
				 }																						// ввод символа
				 else
				 {
					 if (button_registr == 2)															//если регистр "только цифры"
					 { 
						 symbol_new_or_replaced = 0;
						 this->text_form->Text = add_new_sinbol(current_position_cursor, digit_to_add);	//добавляем цифру
						 this->text_form->SelectionStart = current_position_cursor + 1;
					 }
					 else if ((click_button.index_button != digit_to_add)								//если до этого была нажата другая кнопка
						  || (difftime(start, click_button.start) > 1)									//если интервал между нажатиями больше 1 секунды
						  || (current_position_cursor == 0))											//если курсор находится в начале поля ввода
					 { 
						 symbol_new_or_replaced = 0;
						 simbol_to_add = set_registr(button_registr, button_text[0]);					//выясняем, какой регистр у добавляемого символа
 						 this->text_form->Text = add_new_sinbol(current_position_cursor, simbol_to_add);//добавляем новый символ справа от курсора
						 this->text_form->SelectionStart = current_position_cursor + 1;
					 }
					 else if (difftime(start, click_button.start) <= 1)									//если интервал между нажатиями меньше 1 секунды
					 {
						 symbol_new_or_replaced = 1;
						 simbol_to_add = set_registr(button_registr, button_text[click_button.index_simbol]);//выясняем, какой регистр у добавляемого символа
						 if (click_button.index_simbol == length_button_text-1)							//
						 {																				//
							 click_button.index_simbol = 0;												//	
						 }																				//в зависимости от индекса добавляемого символа...
						 else																			//
						 {																				//
							 click_button.index_simbol = click_button.index_simbol + 1;					//
						 }																				//
						 this->text_form->Text = replace_simbol(current_position_cursor, simbol_to_add);//...заменяем символ, стояший слева от курсора новым
						 this->text_form->SelectionStart = current_position_cursor;
					 }
					 click_button.index_button = digit_to_add;											//говорим, что мы нажали кнопку digit_to_add
					 click_button.start = start;
				 }
				 this->text_form->Focus();																//возвращаем фокус (курсор) полю ввода

	}
	//
	//в зависимости от значения регистра button_registr устанавливаем лейбл в правом нижнем углу поля ввода 
	//
	void to_state_label_in_textform(int button_registr)
	{
		switch(button_registr)
		{
		case 0:
			this->label1->Text = "Aa";
			break;
		case 1: 
			this->label1->Text = "AA";
			break;
		case 2: 
			this->label1->Text = "123";
			break;
		case 3: 
			this->label1->Text = "aa";
			break;
		}
	}		 
	//
	//опустошаем поле ввода
	//
	String^ state_empty_textform()
	{
		this->text_form->Text  = "";
		if (button_registr != 2)											//устанавливаем режим "Аа"
		{
			button_registr = 0;
			to_state_label_in_textform(button_registr);
		}
		else																//устанавливаем режим "123"
		{
			button_registr = 2;
			to_state_label_in_textform(button_registr);
		 }
		this->text_form->Focus();
		click_button.index_button = '-1';									//
		click_button.index_simbol = 0;										// говорим, что никакая символьная кнопка не нажата
		click_button.start = 0;												//
		return this->text_form->Text;
	}


	//
	//добавляем символ simbol_to_add справа от текущей позиции курсора
	//
	String^ add_new_sinbol(int current_position_cursor, wchar_t simbol_to_add)
				 {
					 String^ string_start_text = this->text_form->Text->Substring(0, current_position_cursor);		//строка от начала поля ввода до текущего положения курсора
					 String^ string_end_text = this->text_form->Text->Substring(current_position_cursor);			//строка от текущего положения курсора до конца текста
					 String^ string_texform_text = this->text_form->Text->Concat(string_start_text, simbol_to_add, string_end_text);
					 click_button.index_simbol = 1;
					 return string_texform_text;
				 }
	//
	//заменяем символ simbol_to_add слева от текущей позиции курсора
	//
	String^ replace_simbol(int current_position_cursor, wchar_t simbol_to_add)
				 {
					 String^ string_start_text = this->text_form->Text->Substring(0, current_position_cursor-1);	//строка от начала поля ввода до текущего положения курсора - 1
					 String^ string_end_text = this->text_form->Text->Substring(current_position_cursor);			//строка от текущего положения курсора до конца текста
					 String^ string_texform_text = this->text_form->Text->Concat(string_start_text, simbol_to_add, string_end_text);
					 return string_texform_text;
				 }
	//
	//в зависимости от значения регистра i_flag_registr меняем символ add_simbol со строчного на прописной или наоборот
	//
	wchar_t set_registr(int &button_registr, wchar_t add_simbol)
				 {
					 switch(button_registr)
					 {
					 case 0: 
						 add_simbol = toupper(add_simbol);
						 break;
					 case 1: 
						 add_simbol = toupper(add_simbol);
						 break;
					 case 2: 
						 break;
					 case 3: 
						 add_simbol = towlower(add_simbol);
						 break;
					 }		 
					 return add_simbol;
				 }


	//
	//смена регистров после нажатия комбинации Б{Б}П{П}, где Б - символ ".", "!", "?", П - пробел
	//
	bool change_registr_if_point_and_space(String^ text_in_form, int current_position_cursor)
	{
		if ((current_position_cursor != 0) && (text_in_form[current_position_cursor-1] == ' '))
		{
			for (int i = current_position_cursor-1; i >= 0; i--)
			{
				if ((text_in_form[i] == '.')				//
				|| (text_in_form[i] == '!')					//если нам встретилась комбинация Б{Б}П{П}...
				|| (text_in_form[i] == '?'))				//
				{
					return true;							//возвращаем true
				}
			}
		}//if (text_in_form[current_position_cursor - 1] == ' ')
		else 
		{
			return false;									//возвращаем false
		}
	}
	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->abc2 = (gcnew System::Windows::Forms::Button());
			this->def3 = (gcnew System::Windows::Forms::Button());
			this->dell_one = (gcnew System::Windows::Forms::Button());
			this->dell_all = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->text_form = (gcnew System::Windows::Forms::TextBox());
			this->ghi4 = (gcnew System::Windows::Forms::Button());
			this->jkl5 = (gcnew System::Windows::Forms::Button());
			this->mno6 = (gcnew System::Windows::Forms::Button());
			this->_0 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->pqrs7 = (gcnew System::Windows::Forms::Button());
			this->tuv8 = (gcnew System::Windows::Forms::Button());
			this->wxyz9 = (gcnew System::Windows::Forms::Button());
			this->registrs = (gcnew System::Windows::Forms::Button());
			this->right = (gcnew System::Windows::Forms::Button());
			this->left = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// abc2
			// 
			this->abc2->Location = System::Drawing::Point(94, 142);
			this->abc2->Name = L"abc2";
			this->abc2->Size = System::Drawing::Size(54, 21);
			this->abc2->TabIndex = 5;
			this->abc2->Text = L"abc2";
			this->abc2->UseVisualStyleBackColor = true;
			this->abc2->Click += gcnew System::EventHandler(this, &Form1::abc2_Click_1);
			// 
			// def3
			// 
			this->def3->Location = System::Drawing::Point(156, 142);
			this->def3->Name = L"def3";
			this->def3->Size = System::Drawing::Size(54, 21);
			this->def3->TabIndex = 1;
			this->def3->Text = L"def3";
			this->def3->UseVisualStyleBackColor = true;
			this->def3->Click += gcnew System::EventHandler(this, &Form1::def3_Click);
			// 
			// dell_one
			// 
			this->dell_one->Location = System::Drawing::Point(94, 104);
			this->dell_one->Name = L"dell_one";
			this->dell_one->Size = System::Drawing::Size(54, 23);
			this->dell_one->TabIndex = 2;
			this->dell_one->Text = L"dell_one";
			this->dell_one->UseVisualStyleBackColor = true;
			this->dell_one->Click += gcnew System::EventHandler(this, &Form1::dell_one_Click);
			// 
			// dell_all
			// 
			this->dell_all->Location = System::Drawing::Point(34, 251);
			this->dell_all->Name = L"dell_all";
			this->dell_all->Size = System::Drawing::Size(54, 23);
			this->dell_all->TabIndex = 3;
			this->dell_all->Text = L"dell_all";
			this->dell_all->UseVisualStyleBackColor = true;
			this->dell_all->Click += gcnew System::EventHandler(this, &Form1::dell_all_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->label1->Location = System::Drawing::Point(196, 63);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(20, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Aa";
			// 
			// text_form
			// 
			this->text_form->AccessibleRole = System::Windows::Forms::AccessibleRole::Cursor;
			this->text_form->Location = System::Drawing::Point(20, 12);
			this->text_form->Multiline = true;
			this->text_form->Name = L"text_form";
			this->text_form->Size = System::Drawing::Size(203, 70);
			this->text_form->TabIndex = 0;
			// 
			// ghi4
			// 
			this->ghi4->Location = System::Drawing::Point(34, 178);
			this->ghi4->Name = L"ghi4";
			this->ghi4->Size = System::Drawing::Size(54, 21);
			this->ghi4->TabIndex = 6;
			this->ghi4->Text = L"ghi4";
			this->ghi4->UseVisualStyleBackColor = true;
			this->ghi4->Click += gcnew System::EventHandler(this, &Form1::ghi4_Click);
			// 
			// jkl5
			// 
			this->jkl5->Location = System::Drawing::Point(94, 178);
			this->jkl5->Name = L"jkl5";
			this->jkl5->Size = System::Drawing::Size(54, 21);
			this->jkl5->TabIndex = 7;
			this->jkl5->Text = L"jkl5";
			this->jkl5->UseVisualStyleBackColor = true;
			this->jkl5->Click += gcnew System::EventHandler(this, &Form1::jkl5_Click);
			// 
			// mno6
			// 
			this->mno6->Location = System::Drawing::Point(156, 178);
			this->mno6->Name = L"mno6";
			this->mno6->Size = System::Drawing::Size(54, 21);
			this->mno6->TabIndex = 8;
			this->mno6->Text = L"mno6";
			this->mno6->UseVisualStyleBackColor = true;
			this->mno6->Click += gcnew System::EventHandler(this, &Form1::mno6_Click);
			// 
			// _0
			// 
			this->_0->Location = System::Drawing::Point(94, 253);
			this->_0->Name = L"_0";
			this->_0->Size = System::Drawing::Size(54, 21);
			this->_0->TabIndex = 9;
			this->_0->Text = L" 0";
			this->_0->UseVisualStyleBackColor = true;
			this->_0->Click += gcnew System::EventHandler(this, &Form1::_0_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(34, 142);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(54, 21);
			this->button3->TabIndex = 10;
			this->button3->Text = L".,\?!1";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// pqrs7
			// 
			this->pqrs7->Location = System::Drawing::Point(34, 214);
			this->pqrs7->Name = L"pqrs7";
			this->pqrs7->Size = System::Drawing::Size(54, 21);
			this->pqrs7->TabIndex = 11;
			this->pqrs7->Text = L"pqrs7";
			this->pqrs7->UseVisualStyleBackColor = true;
			this->pqrs7->Click += gcnew System::EventHandler(this, &Form1::pqrs7_Click);
			// 
			// tuv8
			// 
			this->tuv8->Location = System::Drawing::Point(94, 214);
			this->tuv8->Name = L"tuv8";
			this->tuv8->Size = System::Drawing::Size(54, 21);
			this->tuv8->TabIndex = 12;
			this->tuv8->Text = L"tuv8";
			this->tuv8->UseVisualStyleBackColor = true;
			this->tuv8->Click += gcnew System::EventHandler(this, &Form1::tuv8_Click);
			// 
			// wxyz9
			// 
			this->wxyz9->Location = System::Drawing::Point(156, 214);
			this->wxyz9->Name = L"wxyz9";
			this->wxyz9->Size = System::Drawing::Size(54, 21);
			this->wxyz9->TabIndex = 13;
			this->wxyz9->Text = L"wxyz9";
			this->wxyz9->UseVisualStyleBackColor = true;
			this->wxyz9->Click += gcnew System::EventHandler(this, &Form1::wxyz9_Click);
			// 
			// registrs
			// 
			this->registrs->Location = System::Drawing::Point(156, 253);
			this->registrs->Name = L"registrs";
			this->registrs->Size = System::Drawing::Size(54, 21);
			this->registrs->TabIndex = 14;
			this->registrs->Text = L"#";
			this->registrs->UseVisualStyleBackColor = true;
			this->registrs->Click += gcnew System::EventHandler(this, &Form1::registrs_Click);
			// 
			// right
			// 
			this->right->Location = System::Drawing::Point(156, 104);
			this->right->Name = L"right";
			this->right->Size = System::Drawing::Size(54, 23);
			this->right->TabIndex = 15;
			this->right->Text = L"right";
			this->right->UseVisualStyleBackColor = true;
			this->right->Click += gcnew System::EventHandler(this, &Form1::right_Click);
			// 
			// left
			// 
			this->left->Location = System::Drawing::Point(34, 104);
			this->left->Name = L"left";
			this->left->Size = System::Drawing::Size(54, 23);
			this->left->TabIndex = 16;
			this->left->Text = L"left";
			this->left->UseVisualStyleBackColor = true;
			this->left->Click += gcnew System::EventHandler(this, &Form1::left_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(238, 297);
			this->Controls->Add(this->left);
			this->Controls->Add(this->right);
			this->Controls->Add(this->registrs);
			this->Controls->Add(this->wxyz9);
			this->Controls->Add(this->tuv8);
			this->Controls->Add(this->pqrs7);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->_0);
			this->Controls->Add(this->mno6);
			this->Controls->Add(this->jkl5);
			this->Controls->Add(this->ghi4);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->dell_all);
			this->Controls->Add(this->dell_one);
			this->Controls->Add(this->def3);
			this->Controls->Add(this->abc2);
			this->Controls->Add(this->text_form);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 this->text_form->MaxLength = 80; //установили максимальную длину сообщения
				 this->text_form->TabIndex = 0;
				 i_flag_registr = 0; //в начале работы установлен регистр Аа
				 click_button.index_button = '-1';//
				 click_button.index_simbol = 0;// никакая кнопка не нажата
				 click_button.start = 0;	   //
				 button_registr = 0;
				 symbol_new_or_replaced = -1;//новый символ

			 }
	//
	//если мы нажали на кнопку удаления всех символов из поля ввода
	//
	private: System::Void dell_all_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				this->text_form->Text = state_empty_textform(); //очищаем поле ввода	 
				symbol_new_or_replaced = -1;//новый символ
			 }
	//
	//если мы нажали на кнопку удаления одного символа из поля ввода
	//
	private: System::Void dell_one_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 if ((this->text_form->Text->Length == 1) && (this->text_form->SelectionStart != 0 ))
				 {
					 this->text_form->Text = state_empty_textform();						//очищаем поле ввода	 
				 }
				 else if (this->text_form->SelectionStart != 0 )
				 {
						 int i_cursor_pozition = this->text_form->SelectionStart-1;
						 this->text_form->Text = this->text_form->Text->Remove(this->text_form->SelectionStart-1, 1);
						 this->text_form->SelectionStart =  i_cursor_pozition;
				 }
				 this->text_form->Focus();
				 symbol_new_or_replaced = -1;
			 }
	//
	//если мы нажали на кнопку перемещения курсора влево
	//
	private: System::Void left_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 if (this->text_form->SelectionStart > 0 )
				 {
					this->text_form->SelectionStart = this->text_form->SelectionStart - 1;	//сдвигаемся на 1 позицию влево		
				 }
				 this->text_form->Focus();
				 symbol_new_or_replaced = 1;
			 }
	//
	//если мы нажали на кнопку перемещения курсора вправо
	//
	private: System::Void right_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				this->text_form->SelectionStart = this->text_form->SelectionStart + 1;		//сдвигаемся на 1 позицию вправо
				this->text_form->Focus();
				symbol_new_or_replaced = 1;
			 }
	//
	//если мы нажали на кнопку "1"
	//
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 String^ button_text = this->button3->Text;
				 int length_button_text = this->button3->Text->Length;
				 add_simbol_in_textform(button_text, length_button_text, button_registr);	//добавляем символ с кнопки ".,?!1"
			 }
	//
	//если мы нажали на кнопку "2"
	//
	private: System::Void abc2_Click_1(System::Object^  sender, System::EventArgs^  e) 
			 {
				 String^ button_text = this->abc2->Text;
				 int length_button_text = this->abc2->Text->Length;
				 add_simbol_in_textform(button_text, length_button_text, button_registr);	//добавляем символ с кнопки "abc2"		
			 }

	//
	//если мы нажали на кнопку "3"
	//
	private: System::Void def3_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 String^ button_text = this->def3->Text;
				 int length_button_text = this->def3->Text->Length;
				 add_simbol_in_textform(button_text, length_button_text, button_registr);	//добавляем символ с кнопки "def3"			 

				 
			 }
    //
	//если мы нажали на кнопку "4"
	//
	private: System::Void ghi4_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 String^ button_text = this->ghi4->Text;
				 int length_button_text = this->ghi4->Text->Length;
				 add_simbol_in_textform(button_text, length_button_text, button_registr);	//добавляем символ с кнопки "ghi4"		 

			 }
	//
	//если мы нажали на кнопку "5"
	//
	private: System::Void jkl5_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 String^ button_text = this->jkl5->Text;
				 int length_button_text = this->jkl5->Text->Length;
				 add_simbol_in_textform(button_text, length_button_text, button_registr);	//добавляем символ с кнопки "jkl5"			 

			 }
	//
	//если мы нажали на кнопку "6"
	//
	private: System::Void mno6_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 String^ button_text = this->mno6->Text;
				 int length_button_text = this->mno6->Text->Length;
				 add_simbol_in_textform(button_text, length_button_text, button_registr);	//добавляем символ с кнопки "mno6"				 
			 }
	//
	//если мы нажали на кнопку "7"
	//
	private: System::Void pqrs7_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 String^ button_text = this->pqrs7->Text;
				 int length_button_text = this->pqrs7->Text->Length;
				 add_simbol_in_textform(button_text, length_button_text, button_registr);	//добавляем символ с кнопки "pqrs7"
			 }

    //
	//если мы нажали на кнопку "8"
	//
	private: System::Void tuv8_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 String^ button_text = this->tuv8->Text;
				 int length_button_text = this->tuv8->Text->Length;
				 add_simbol_in_textform(button_text, length_button_text, button_registr);	//добавляем символ с кнопки "tuv8"
			 }
    //
	//если мы нажали на кнопку "9"
	//
	private: System::Void wxyz9_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 
				 String^ button_text = this->wxyz9->Text;
				 int length_button_text = this->wxyz9->Text->Length;
				 add_simbol_in_textform(button_text, length_button_text, button_registr);	//добавляем символ с кнопки "wxyz9"

			 }
    //
	//если мы нажали на кнопку "0"
	//
	private: System::Void _0_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 String^ button_text = this->_0->Text;
				 int length_button_text = this->_0->Text->Length;
				 add_simbol_in_textform(button_text, length_button_text, button_registr);	//добавляем символ с кнопки " 0"

			 }
	//
	//если мы нажали на кнопку смены регистров
	//
	private: System::Void registrs_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 symbol_new_or_replaced = -1;
				 click_button.index_button = '-1';//
				 click_button.index_simbol = 0;// никакая кнопка не нажата
				 click_button.start = 0;	   //
				 switch(button_registr)
						 {
						 case 0: 
							 button_registr = 1;
							 to_state_label_in_textform(button_registr);
							 break;
						 case 1: 
							 button_registr = 2;
							 to_state_label_in_textform(button_registr);
							 break;
						case 2: 
							 button_registr = 3;
							 to_state_label_in_textform(button_registr);
							 break;
						 case 3: 
							 button_registr = 0;
							 to_state_label_in_textform(button_registr);
							 break;
						 }
				 this->text_form->Focus(); //возвращаем фокус (курсор) полю ввода
			 }
};
}

