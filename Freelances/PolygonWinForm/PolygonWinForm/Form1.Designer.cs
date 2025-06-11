namespace PolygonWinForm
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
            centerX = new TextBox();
            centerY = new TextBox();
            label1 = new Label();
            label2 = new Label();
            length_TextBox = new TextBox();
            label3 = new Label();
            red_trackBar = new TrackBar();
            green_trackBar = new TrackBar();
            label6 = new Label();
            blue_trackBar = new TrackBar();
            label7 = new Label();
            edge_TextBox = new TextBox();
            label4 = new Label();
            label5 = new Label();
            CCW_CheckBox = new CheckBox();
            angle_TextBox = new TextBox();
            label8 = new Label();
            EdgeCords_ListBox = new ListBox();
            textBox4 = new TextBox();
            DrawButton = new Button();
            RotateButton = new Button();
            ResetButton = new Button();
            pictureBox1 = new PictureBox();
            ((System.ComponentModel.ISupportInitialize)red_trackBar).BeginInit();
            ((System.ComponentModel.ISupportInitialize)green_trackBar).BeginInit();
            ((System.ComponentModel.ISupportInitialize)blue_trackBar).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            SuspendLayout();
            // 
            // centerX
            // 
            centerX.Location = new Point(600, 27);
            centerX.Name = "centerX";
            centerX.Size = new Size(30, 23);
            centerX.TabIndex = 0;
            centerX.Text = "0";
            centerX.TextAlign = HorizontalAlignment.Center;
            centerX.KeyPress += OnlyDigit_KeyPress;
            // 
            // centerY
            // 
            centerY.Location = new Point(630, 27);
            centerY.Name = "centerY";
            centerY.Size = new Size(30, 23);
            centerY.TabIndex = 1;
            centerY.Text = "0";
            centerY.TextAlign = HorizontalAlignment.Center;
            centerY.KeyPress += OnlyDigit_KeyPress;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(525, 30);
            label1.Name = "label1";
            label1.Size = new Size(67, 15);
            label1.TabIndex = 2;
            label1.Text = "Center (x,y)";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(536, 59);
            label2.Name = "label2";
            label2.Size = new Size(44, 15);
            label2.TabIndex = 3;
            label2.Text = "Length";
            label2.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // length_TextBox
            // 
            length_TextBox.Location = new Point(600, 56);
            length_TextBox.Name = "length_TextBox";
            length_TextBox.Size = new Size(60, 23);
            length_TextBox.TabIndex = 4;
            length_TextBox.Text = "5";
            length_TextBox.TextAlign = HorizontalAlignment.Center;
            length_TextBox.KeyPress += OnlyDigit_KeyPress;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(536, 97);
            label3.Name = "label3";
            label3.Size = new Size(27, 15);
            label3.TabIndex = 5;
            label3.Text = "Red";
            label3.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // red_trackBar
            // 
            red_trackBar.AutoSize = false;
            red_trackBar.BackColor = Color.White;
            red_trackBar.Location = new Point(580, 97);
            red_trackBar.Maximum = 255;
            red_trackBar.Name = "red_trackBar";
            red_trackBar.Size = new Size(94, 26);
            red_trackBar.TabIndex = 8;
            red_trackBar.TickStyle = TickStyle.None;
            // 
            // green_trackBar
            // 
            green_trackBar.AutoSize = false;
            green_trackBar.BackColor = Color.White;
            green_trackBar.Location = new Point(580, 129);
            green_trackBar.Maximum = 255;
            green_trackBar.Name = "green_trackBar";
            green_trackBar.Size = new Size(94, 26);
            green_trackBar.TabIndex = 10;
            green_trackBar.TickStyle = TickStyle.None;
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(536, 129);
            label6.Name = "label6";
            label6.Size = new Size(38, 15);
            label6.TabIndex = 9;
            label6.Text = "Green";
            label6.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // blue_trackBar
            // 
            blue_trackBar.AutoSize = false;
            blue_trackBar.BackColor = Color.White;
            blue_trackBar.Location = new Point(580, 161);
            blue_trackBar.Maximum = 255;
            blue_trackBar.Name = "blue_trackBar";
            blue_trackBar.Size = new Size(94, 26);
            blue_trackBar.TabIndex = 12;
            blue_trackBar.TickStyle = TickStyle.None;
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Location = new Point(536, 161);
            label7.Name = "label7";
            label7.Size = new Size(30, 15);
            label7.TabIndex = 11;
            label7.Text = "Blue";
            label7.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // edge_TextBox
            // 
            edge_TextBox.Location = new Point(575, 214);
            edge_TextBox.Name = "edge_TextBox";
            edge_TextBox.Size = new Size(45, 23);
            edge_TextBox.TabIndex = 14;
            edge_TextBox.Text = "5";
            edge_TextBox.TextAlign = HorizontalAlignment.Center;
            edge_TextBox.KeyPress += OnlyDigit_KeyPress;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(536, 217);
            label4.Name = "label4";
            label4.Size = new Size(33, 15);
            label4.TabIndex = 13;
            label4.Text = "Edge";
            label4.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(626, 217);
            label5.Name = "label5";
            label5.Size = new Size(34, 15);
            label5.TabIndex = 15;
            label5.Text = "CCW";
            label5.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // CCW_CheckBox
            // 
            CCW_CheckBox.AutoSize = true;
            CCW_CheckBox.Location = new Point(666, 217);
            CCW_CheckBox.Name = "CCW_CheckBox";
            CCW_CheckBox.Size = new Size(15, 14);
            CCW_CheckBox.TabIndex = 16;
            CCW_CheckBox.UseVisualStyleBackColor = true;
            // 
            // angle_TextBox
            // 
            angle_TextBox.Location = new Point(600, 243);
            angle_TextBox.Name = "angle_TextBox";
            angle_TextBox.Size = new Size(60, 23);
            angle_TextBox.TabIndex = 18;
            angle_TextBox.Text = "30";
            angle_TextBox.TextAlign = HorizontalAlignment.Center;
            angle_TextBox.KeyPress += OnlyDigit_KeyPress;
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Location = new Point(536, 246);
            label8.Name = "label8";
            label8.Size = new Size(38, 15);
            label8.TabIndex = 17;
            label8.Text = "Angle";
            label8.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // EdgeCords_ListBox
            // 
            EdgeCords_ListBox.FormattingEnabled = true;
            EdgeCords_ListBox.ItemHeight = 15;
            EdgeCords_ListBox.Location = new Point(536, 315);
            EdgeCords_ListBox.Name = "EdgeCords_ListBox";
            EdgeCords_ListBox.Size = new Size(124, 94);
            EdgeCords_ListBox.TabIndex = 19;
            EdgeCords_ListBox.Tag = "";
            // 
            // textBox4
            // 
            textBox4.Location = new Point(536, 286);
            textBox4.Name = "textBox4";
            textBox4.ReadOnly = true;
            textBox4.Size = new Size(124, 23);
            textBox4.TabIndex = 20;
            textBox4.Text = "EdgeCoordinates";
            textBox4.TextAlign = HorizontalAlignment.Center;
            // 
            // DrawButton
            // 
            DrawButton.FlatStyle = FlatStyle.Flat;
            DrawButton.Location = new Point(536, 415);
            DrawButton.Name = "DrawButton";
            DrawButton.Size = new Size(124, 23);
            DrawButton.TabIndex = 21;
            DrawButton.Text = "Draw";
            DrawButton.UseVisualStyleBackColor = true;
            DrawButton.Click += DrawButton_Click;
            // 
            // RotateButton
            // 
            RotateButton.FlatStyle = FlatStyle.Flat;
            RotateButton.Location = new Point(536, 444);
            RotateButton.Name = "RotateButton";
            RotateButton.Size = new Size(124, 23);
            RotateButton.TabIndex = 22;
            RotateButton.Text = "Rotate";
            RotateButton.UseVisualStyleBackColor = true;
            RotateButton.Click += RotateButton_Click;
            // 
            // ResetButton
            // 
            ResetButton.FlatStyle = FlatStyle.Flat;
            ResetButton.Location = new Point(536, 473);
            ResetButton.Name = "ResetButton";
            ResetButton.Size = new Size(124, 23);
            ResetButton.TabIndex = 23;
            ResetButton.Text = "Reset";
            ResetButton.UseVisualStyleBackColor = true;
            ResetButton.Click += ResetButton_Click;
            // 
            // pictureBox1
            // 
            pictureBox1.BorderStyle = BorderStyle.FixedSingle;
            pictureBox1.Location = new Point(12, 12);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(500, 500);
            pictureBox1.TabIndex = 24;
            pictureBox1.TabStop = false;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(697, 522);
            Controls.Add(pictureBox1);
            Controls.Add(ResetButton);
            Controls.Add(RotateButton);
            Controls.Add(DrawButton);
            Controls.Add(textBox4);
            Controls.Add(EdgeCords_ListBox);
            Controls.Add(angle_TextBox);
            Controls.Add(label8);
            Controls.Add(CCW_CheckBox);
            Controls.Add(label5);
            Controls.Add(edge_TextBox);
            Controls.Add(label4);
            Controls.Add(blue_trackBar);
            Controls.Add(label7);
            Controls.Add(green_trackBar);
            Controls.Add(label6);
            Controls.Add(red_trackBar);
            Controls.Add(label3);
            Controls.Add(length_TextBox);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(centerY);
            Controls.Add(centerX);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)red_trackBar).EndInit();
            ((System.ComponentModel.ISupportInitialize)green_trackBar).EndInit();
            ((System.ComponentModel.ISupportInitialize)blue_trackBar).EndInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox centerX;
        private TextBox centerY;
        private Label label1;
        private Label label2;
        private TextBox length_TextBox;
        private Label label3;
        private TrackBar red_trackBar;
        private TrackBar green_trackBar;
        private Label label6;
        private TrackBar blue_trackBar;
        private Label label7;
        private TextBox edge_TextBox;
        private Label label4;
        private Label label5;
        private CheckBox CCW_CheckBox;
        private TextBox angle_TextBox;
        private Label label8;
        private ListBox EdgeCords_ListBox;
        private TextBox textBox4;
        private Button DrawButton;
        private Button RotateButton;
        private Button ResetButton;
        private PictureBox pictureBox1;
    }
}
