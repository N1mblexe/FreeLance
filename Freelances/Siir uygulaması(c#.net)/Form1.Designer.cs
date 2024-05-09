namespace Bionluk_c__1
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
            listBox1 = new ListBox();
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            label4 = new Label();
            label5 = new Label();
            button1 = new Button();
            txtYazar = new TextBox();
            txtSiirAdi = new TextBox();
            txtSatirSayisi = new TextBox();
            txtBesteleyen = new TextBox();
            txtTarih = new TextBox();
            SuspendLayout();
            // 
            // listBox1
            // 
            listBox1.FormattingEnabled = true;
            listBox1.ItemHeight = 15;
            listBox1.Location = new Point(134, 288);
            listBox1.Name = "listBox1";
            listBox1.Size = new Size(514, 94);
            listBox1.TabIndex = 0;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(134, 26);
            label1.Name = "label1";
            label1.Size = new Size(56, 15);
            label1.TabIndex = 1;
            label1.Text = "Şiir yazarı";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(134, 64);
            label2.Name = "label2";
            label2.Size = new Size(42, 15);
            label2.TabIndex = 2;
            label2.Text = "Şiir adı";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(134, 105);
            label3.Name = "label3";
            label3.Size = new Size(61, 15);
            label3.TabIndex = 3;
            label3.Text = "Satır sayısı";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(134, 147);
            label4.Name = "label4";
            label4.Size = new Size(85, 15);
            label4.TabIndex = 4;
            label4.Text = "Şiiri besteleyen";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(134, 182);
            label5.Name = "label5";
            label5.Size = new Size(98, 15);
            label5.TabIndex = 5;
            label5.Text = "Bestelendiği tarih";
            // 
            // button1
            // 
            button1.Location = new Point(325, 223);
            button1.Name = "button1";
            button1.Size = new Size(323, 38);
            button1.TabIndex = 6;
            button1.Text = "Şiiri Ekle";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // txtYazar
            // 
            txtYazar.AccessibleDescription = "txtYazar";
            txtYazar.AccessibleName = "txtYazar";
            txtYazar.Location = new Point(325, 18);
            txtYazar.Name = "txtYazar";
            txtYazar.Size = new Size(323, 23);
            txtYazar.TabIndex = 7;
            // 
            // txtSiirAdi
            // 
            txtSiirAdi.AccessibleName = "txtSiirAdi";
            txtSiirAdi.Location = new Point(325, 61);
            txtSiirAdi.Name = "txtSiirAdi";
            txtSiirAdi.Size = new Size(323, 23);
            txtSiirAdi.TabIndex = 7;
            // 
            // txtSatirSayisi
            // 
            txtSatirSayisi.AccessibleName = "txtSatirSayisi";
            txtSatirSayisi.Location = new Point(325, 97);
            txtSatirSayisi.Name = "txtSatirSayisi";
            txtSatirSayisi.Size = new Size(323, 23);
            txtSatirSayisi.TabIndex = 7;
            // 
            // txtBesteleyen
            // 
            txtBesteleyen.Location = new Point(325, 139);
            txtBesteleyen.Name = "txtBesteleyen";
            txtBesteleyen.Size = new Size(323, 23);
            txtBesteleyen.TabIndex = 7;
            // 
            // txtTarih
            // 
            txtTarih.Location = new Point(325, 174);
            txtTarih.Name = "txtTarih";
            txtTarih.Size = new Size(323, 23);
            txtTarih.TabIndex = 7;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(txtTarih);
            Controls.Add(txtBesteleyen);
            Controls.Add(txtSatirSayisi);
            Controls.Add(txtSiirAdi);
            Controls.Add(txtYazar);
            Controls.Add(button1);
            Controls.Add(label5);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(listBox1);
            Name = "Form1";
            Text = "Form1";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ListBox listBox1;
        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private Label label5;
        private Button button1;
        private TextBox txtYazar;
        private TextBox txtSiirAdi;
        private TextBox txtSatirSayisi;
        private TextBox txtBesteleyen;
        private TextBox txtTarih;
    }
}