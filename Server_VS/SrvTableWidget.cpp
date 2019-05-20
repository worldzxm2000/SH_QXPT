#include "SrvTableWidget.h"
#include<QHeaderview>
#include<QMessageBox>
#include<QDateTimeEdit.h>
#include<QComboBox.h>
#include<QSpinBox>
#include<QLabel>
#include<QGridLayout>
#include"SwitchButton.h"
SrvTableWidget::SrvTableWidget(QWidget *parent)
	:QTableWidget(parent)
{
	setColumnCount(2);
	sortby = false;
	int row = 0;
	QStringList headerlist;
	setShowGrid(false);
	headerlist.append(QString::fromLocal8Bit("业务类型"));
	headerlist.append(QString::fromLocal8Bit("业务名称"));
	setHorizontalHeaderLabels(headerlist);
	this->verticalHeader()->setHidden(true);// 隐藏行号 
	setColumnHidden(1, true);//隐藏业务名称
	setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
	horizontalHeader()->setHighlightSections(false);//禁止表头选中高亮
	horizontalHeader()->setStyleSheet("QHeaderView{border:none; border-bottom:2px solid white; min-height: 30px;}"
		"QHeaderView::section{ background:rgb(46,80,108);margin-left:0px;border:2px;border-color:red;}"
	);
	setColumnWidth(0,180);//设置宽度为180
	horizontalHeader()->setStretchLastSection(true);//列宽
	connect(this->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(record_sortbyclounm(int)));
}

SrvTableWidget::~SrvTableWidget()
{
}

//添加行
void SrvTableWidget::AddRow(QString header="header")
{
	int rowIndex = this->rowCount();
	setRowCount(rowIndex+1);
	//第二列
	QTableWidgetItem *thirdTableWidgetItem = new QTableWidgetItem(header);
	setItem(rowIndex, 1, thirdTableWidgetItem);
	//第一列
	QWidget *Grid = new QWidget(this);
	Grid->setStyleSheet("QWidget{ background:transparent; border-color:transparent}");
	//一个文本加一个按钮
	QLabel *NameLabel = new QLabel(Grid);
	NameLabel->setText(header);
	NameLabel->setStyleSheet("font:12pt");
	NameLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	NameLabel->setGeometry(2, 0, 150, 28);

	SwitchButton *StatusBtn = new SwitchButton(Grid);
	StatusBtn->setButtonStyle(SwitchButton::ButtonStyle::ButtonStyle_Image);
	StatusBtn->setChecked(1);
	StatusBtn->setGeometry(150, 0, 80, 28);
	connect(StatusBtn, SIGNAL(checkedChanged(bool)), this, SLOT(On_Run_Btn(bool)));

	setCellWidget(rowIndex, 0, Grid);
}
//运行按钮
void SrvTableWidget::On_Run_Btn(bool Checked)
{
	SwitchButton *senderObj = qobject_cast<SwitchButton*>(sender());
	if (senderObj == nullptr)
		return;
	QWidget *Parent = senderObj->parentWidget();
	QModelIndex idx = this->indexAt(Parent->pos());
	int row = idx.row();
	Checked==true? NoticfyServerRun(row): NoticfyServerStop(row);
}


//排序
void SrvTableWidget::record_sortbyclounm(int colum)
{
	if (colum >= this->columnCount() || colum < 0)
		return;
	if (sortby)
	{
		this->sortItems(colum+1, Qt::AscendingOrder);
		sortby = !sortby;
	}
	else
	{
		this->sortItems(colum+1, Qt::DescendingOrder);
		sortby = !sortby;
	}

}
