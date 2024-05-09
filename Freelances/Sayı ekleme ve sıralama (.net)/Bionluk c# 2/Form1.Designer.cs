namespace Bionluk_c__2
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            Sort_BK = new Button();
            SORT_KB = new Button();
            SayiEkle = new Button();
            listBox1 = new ListBox();
            input = new TextBox();
            listBox2 = new ListBox();
            infı = new Label();
            SuspendLayout();
            // 
            // Sort_BK
            // 
            Sort_BK.BackColor = Color.Red;
            Sort_BK.Location = new Point(344, 315);
            Sort_BK.Name = "Sort_BK";
            Sort_BK.Size = new Size(147, 46);
            Sort_BK.TabIndex = 0;
            Sort_BK.Text = "Sort_BK";
            Sort_BK.UseVisualStyleBackColor = false;
            Sort_BK.Click += Sort_BK_Click;
            // 
            // SORT_KB
            // 
            SORT_KB.BackColor = SystemColors.MenuHighlight;
            SORT_KB.Location = new Point(344, 254);
            SORT_KB.Name = "SORT_KB";
            SORT_KB.Size = new Size(147, 46);
            SORT_KB.TabIndex = 0;
            SORT_KB.Text = "Sort_KB";
            SORT_KB.UseVisualStyleBackColor = false;
            SORT_KB.Click += Sort_KB_Click;
            // 
            // SayiEkle
            // 
            SayiEkle.Location = new Point(155, 149);
            SayiEkle.Name = "SayiEkle";
            SayiEkle.Size = new Size(111, 41);
            SayiEkle.TabIndex = 0;
            SayiEkle.Text = "Sayı Ekle";
            SayiEkle.UseVisualStyleBackColor = true;
            SayiEkle.Click += button1_Click;
            // 
            // listBox1
            // 
            listBox1.FormattingEnabled = true;
            listBox1.ItemHeight = 15;
            listBox1.Location = new Point(497, 239);
            listBox1.Name = "listBox1";
            listBox1.Size = new Size(245, 139);
            listBox1.TabIndex = 1;
            // 
            // input
            // 
            input.Location = new Point(135, 120);
            input.Name = "input";
            input.Size = new Size(143, 23);
            input.TabIndex = 2;
            // 
            // listBox2
            // 
            listBox2.FormattingEnabled = true;
            listBox2.ItemHeight = 15;
            listBox2.Location = new Point(497, 94);
            listBox2.Name = "listBox2";
            listBox2.Size = new Size(245, 139);
            listBox2.TabIndex = 1;
            // 
            // infı
            // 
            infı.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            infı.Location = new Point(115, 94);
            infı.Name = "infı";
            infı.Size = new Size(192, 23);
            infı.TabIndex = 3;
            infı.Text = "Dizi elemanlarını ekleyiniz";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(infı);
            Controls.Add(input);
            Controls.Add(listBox2);
            Controls.Add(listBox1);
            Controls.Add(SayiEkle);
            Controls.Add(SORT_KB);
            Controls.Add(Sort_BK);
            Name = "Form1";
            Text = "Form1";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button Sort_BK;
        private Button SORT_KB;
        private Button SayiEkle;
        private ListBox listBox1;
        private TextBox input;
        private ListBox listBox2;
        private Label infı;
    }
}