namespace PieChart
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea3 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend3 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.Gida = new System.Windows.Forms.Label();
            this.Akaryakit = new System.Windows.Forms.Label();
            this.Saglik = new System.Windows.Forms.Label();
            this.Diger = new System.Windows.Forms.Label();
            this.Egitim = new System.Windows.Forms.Label();
            this.comBox = new System.Windows.Forms.ComboBox();
            this.ButonHesapla = new System.Windows.Forms.Button();
            this.ButonYuzdeHesapla = new System.Windows.Forms.Button();
            this.infoText = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            this.SuspendLayout();
            // 
            // chart1
            // 
            chartArea3.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea3);
            legend3.Name = "Legend1";
            this.chart1.Legends.Add(legend3);
            this.chart1.Location = new System.Drawing.Point(427, 23);
            this.chart1.Name = "chart1";
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Pie;
            series3.Legend = "Legend1";
            series3.Name = "Series1";
            this.chart1.Series.Add(series3);
            this.chart1.Size = new System.Drawing.Size(361, 404);
            this.chart1.TabIndex = 0;
            this.chart1.Text = "chart1";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(186, 23);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(108, 20);
            this.textBox1.TabIndex = 1;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(186, 72);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(108, 20);
            this.textBox2.TabIndex = 1;
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(186, 122);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(108, 20);
            this.textBox3.TabIndex = 1;
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(186, 168);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(108, 20);
            this.textBox4.TabIndex = 1;
            // 
            // textBox5
            // 
            this.textBox5.Location = new System.Drawing.Point(186, 217);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(108, 20);
            this.textBox5.TabIndex = 1;
            // 
            // Gida
            // 
            this.Gida.AutoSize = true;
            this.Gida.Location = new System.Drawing.Point(113, 79);
            this.Gida.Name = "Gida";
            this.Gida.Size = new System.Drawing.Size(29, 13);
            this.Gida.TabIndex = 2;
            this.Gida.Text = "Gıda";
            // 
            // Akaryakit
            // 
            this.Akaryakit.AutoSize = true;
            this.Akaryakit.Location = new System.Drawing.Point(113, 129);
            this.Akaryakit.Name = "Akaryakit";
            this.Akaryakit.Size = new System.Drawing.Size(51, 13);
            this.Akaryakit.TabIndex = 2;
            this.Akaryakit.Text = "Akaryakıt";
            // 
            // Saglik
            // 
            this.Saglik.AutoSize = true;
            this.Saglik.Location = new System.Drawing.Point(113, 175);
            this.Saglik.Name = "Saglik";
            this.Saglik.Size = new System.Drawing.Size(36, 13);
            this.Saglik.TabIndex = 2;
            this.Saglik.Text = "Sağlık";
            // 
            // Diger
            // 
            this.Diger.AutoSize = true;
            this.Diger.Location = new System.Drawing.Point(113, 224);
            this.Diger.Name = "Diger";
            this.Diger.Size = new System.Drawing.Size(32, 13);
            this.Diger.TabIndex = 2;
            this.Diger.Text = "Diğer";
            // 
            // Egitim
            // 
            this.Egitim.AutoSize = true;
            this.Egitim.Location = new System.Drawing.Point(113, 30);
            this.Egitim.Name = "Egitim";
            this.Egitim.Size = new System.Drawing.Size(35, 13);
            this.Egitim.TabIndex = 2;
            this.Egitim.Text = "Eğitim";
            // 
            // comBox
            // 
            this.comBox.FormattingEnabled = true;
            this.comBox.Items.AddRange(new object[] {
            "Egitim",
            "Gida",
            "Akaryakit",
            "Saglik",
            "Diger"});
            this.comBox.Location = new System.Drawing.Point(97, 367);
            this.comBox.Name = "comBox";
            this.comBox.Size = new System.Drawing.Size(121, 21);
            this.comBox.TabIndex = 3;
            // 
            // ButonHesapla
            // 
            this.ButonHesapla.Location = new System.Drawing.Point(116, 269);
            this.ButonHesapla.Name = "ButonHesapla";
            this.ButonHesapla.Size = new System.Drawing.Size(178, 40);
            this.ButonHesapla.TabIndex = 4;
            this.ButonHesapla.Text = "HESAPLA";
            this.ButonHesapla.UseVisualStyleBackColor = true;
            this.ButonHesapla.Click += new System.EventHandler(this.ButonHesapla_Click);
            // 
            // ButonYuzdeHesapla
            // 
            this.ButonYuzdeHesapla.Location = new System.Drawing.Point(236, 367);
            this.ButonYuzdeHesapla.Name = "ButonYuzdeHesapla";
            this.ButonYuzdeHesapla.Size = new System.Drawing.Size(114, 31);
            this.ButonYuzdeHesapla.TabIndex = 4;
            this.ButonYuzdeHesapla.Text = "Yüzde Hesapla";
            this.ButonYuzdeHesapla.UseVisualStyleBackColor = true;
            this.ButonYuzdeHesapla.Click += new System.EventHandler(this.ButonYuzdeHesapla_Click);
            // 
            // infoText
            // 
            this.infoText.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.infoText.AutoSize = true;
            this.infoText.Location = new System.Drawing.Point(183, 414);
            this.infoText.Name = "infoText";
            this.infoText.Size = new System.Drawing.Size(0, 13);
            this.infoText.TabIndex = 2;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.ButonYuzdeHesapla);
            this.Controls.Add(this.ButonHesapla);
            this.Controls.Add(this.comBox);
            this.Controls.Add(this.infoText);
            this.Controls.Add(this.Diger);
            this.Controls.Add(this.Saglik);
            this.Controls.Add(this.Akaryakit);
            this.Controls.Add(this.Egitim);
            this.Controls.Add(this.Gida);
            this.Controls.Add(this.textBox5);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.textBox4);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.chart1);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.Label Gida;
        private System.Windows.Forms.Label Akaryakit;
        private System.Windows.Forms.Label Saglik;
        private System.Windows.Forms.Label Diger;
        private System.Windows.Forms.Label Egitim;
        private System.Windows.Forms.ComboBox comBox;
        private System.Windows.Forms.Button ButonHesapla;
        private System.Windows.Forms.Button ButonYuzdeHesapla;
        private System.Windows.Forms.Label infoText;
    }
}

