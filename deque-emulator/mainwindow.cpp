#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include <algorithm>
#include <numeric>

#include "algo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    std::random_device rd;
    gen_shuffle_ = std::mt19937(rd());
    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() {
    auto preserve_iter = deque_model_.iterator;

    ui->pb_popback->setDisabled(deque_model_.items.empty());
    ui->pb_popfront->setDisabled(deque_model_.items.empty());
    ui->txt_size->setText(QString::number(deque_model_.items.size()));
    ui->list_widget->clear();

    int idx = 0;
    for (const auto& elem : deque_model_.items){
        ui->list_widget->addItem(QString::number(idx++) +": "+ QString::fromStdString(elem));
    }
    ui->list_widget->addItem("end");

    deque_model_.iterator = preserve_iter;
    ApplyIterator();
}

void MainWindow::ApplyIterator()
{
    size_t idx = std::distance(deque_model_.items.begin(), deque_model_.iterator);
    ui->list_widget->setCurrentRow(idx);
    bool isLast = deque_model_.iterator == deque_model_.items.end();
    ui->pb_edit->setDisabled(isLast);
    ui->pb_erase->setDisabled(isLast);
    ui->pb_plusplus->setDisabled(isLast);

    bool isFirst = deque_model_.iterator == deque_model_.items.begin();
    ui->pb_minusminus->setDisabled(isFirst);

    if (isLast){
        ui->txt_elem_content->clear();
    } else {
        ui->txt_elem_content->setText(QString::fromStdString(deque_model_.items[idx]));
    }

}

void MainWindow::resetIterator()
{
    deque_model_.iterator = deque_model_.items.begin();
}

bool MainWindow::isSorted()
{
    return std::is_sorted(deque_model_.items.begin(), deque_model_.items.end());
}


void MainWindow::SetRandomGen(const std::mt19937 &random_gen)
{
    gen_shuffle_ = random_gen;
}



void MainWindow::on_pb_popfront_clicked()
{
    if (!deque_model_.items.empty()){
		deque_model_.items.pop_front();
	}
    resetIterator();
    ApplyModel();
}


void MainWindow::on_pb_pushfront_clicked()
{
    deque_model_.items.push_front(ui->txt_elem_content->text().toStdString());
    resetIterator();
    ApplyModel();
}

void MainWindow::on_pb_popback_clicked()
{
    if (!deque_model_.items.empty()){
		deque_model_.items.pop_back();
	}
    resetIterator();
    ApplyModel();
}

void MainWindow::on_pb_pushback_clicked()
{
    deque_model_.items.push_back(ui->txt_elem_content->text().toStdString());
    resetIterator();
    ApplyModel();
}


void MainWindow::on_pb_clear_clicked()
{
    deque_model_.items.clear();
    resetIterator();
    ApplyModel();
}


void MainWindow::on_pb_tea_clicked()
{
    deque_model_.items.clear();
    deque_model_.items = tea;
    resetIterator();
    ApplyModel();
}


void MainWindow::on_pb_cakes_clicked()
{
    deque_model_.items.clear();
    deque_model_.items = cakes;
    resetIterator();
    ApplyModel();
}


void MainWindow::on_pb_edit_clicked()
{
    *(deque_model_.iterator) = ui->txt_elem_content->text().toStdString();
    ApplyModel();
}


void MainWindow::on_pb_erase_clicked()
{
    deque_model_.iterator = deque_model_.items.erase(deque_model_.iterator);
    resetIterator();
    ApplyModel();
}


void MainWindow::on_pb_insert_clicked()
{
    deque_model_.iterator = deque_model_.items.insert(deque_model_.iterator,ui->txt_elem_content->text().toStdString());
    resetIterator();
    ApplyModel();
}


void MainWindow::on_pb_minusminus_clicked()
{
    deque_model_.iterator--;
    ApplyIterator();
}


void MainWindow::on_pb_plusplus_clicked()
{
    deque_model_.iterator++;
    ApplyIterator();
}


void MainWindow::on_pb_begin_clicked()
{
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_pb_end_clicked()
{
    deque_model_.iterator = deque_model_.items.end();
    ApplyIterator();
}


void MainWindow::on_list_widget_currentRowChanged(int currentRow)
{
    currentRow = std::clamp(currentRow, 0, (int)deque_model_.items.size());
    deque_model_.iterator = deque_model_.items.begin() + currentRow;
    ApplyIterator();
}


void MainWindow::on_pb_resize_clicked()
{
    deque_model_.items.resize(ui->txt_size->text().toInt());
    resetIterator();
    ApplyModel();
}

void MainWindow::on_pb_find_clicked()
{
    if (!deque_model_.items.empty()){
        auto iter = std::find(deque_model_.items.begin(),
                              deque_model_.items.end(),
                              ui->txt_elem_content->text().toStdString()
                              );
        deque_model_.iterator = iter;
        ApplyIterator();
    }

}


void MainWindow::on_pb_maxelem_clicked()
{
    if (!deque_model_.items.empty()){
        auto iter = std::max_element(deque_model_.items.begin(),
                                     deque_model_.items.end(),
                                     [] (const std::string& lhs, const std::string& rhs){
                                         return lhs < rhs;
                                     }
                                     );
        if (iter != deque_model_.items.end()){
            deque_model_.iterator = iter;
            ApplyIterator();
        }
    }
}


void MainWindow::on_pb_minelem_clicked()
{
    if (!deque_model_.items.empty()){
        auto iter = std::min_element(deque_model_.items.begin(),
                                     deque_model_.items.end(),
                                     [] (const std::string& lhs, const std::string& rhs){
                                         return lhs < rhs;
                                     }
                                     );
        if (iter != deque_model_.items.end()){
            deque_model_.iterator = iter;
            ApplyIterator();
        }
    }
}


void MainWindow::on_pb_count_clicked()
{
    int result = 0;
    if (!deque_model_.items.empty()){
        result = std::count(deque_model_.items.begin(),
                            deque_model_.items.end(),
                            ui->le_count->text().toStdString()
                            );
    }
    ui->lbl_count->setText(QString::number(result));
}


void MainWindow::on_pb_sort_clicked()
{
    if (deque_model_.items.empty()){
		return;
	}
    auto comp = [](const std::string& lhs, const std::string& rhs) {return lhs < rhs;};
    deque_model_.items = MergeSort<std::string, decltype(comp)>(deque_model_.items, comp);
    resetIterator();
    ApplyModel();
}


void MainWindow::on_pb_sort2_clicked()
{
    if (deque_model_.items.empty()){
		return;
	}
    auto comp = [](const std::string& lhs, const std::string& rhs) {
        return QString::compare(QString::fromStdString(lhs),QString::fromStdString(rhs),Qt::CaseInsensitive) < 0;
    };
    deque_model_.items = MergeSort<std::string, decltype(comp)>(deque_model_.items, comp);
    resetIterator();
    ApplyModel();
}


void MainWindow::on_pb_unique_clicked()
{
    if (deque_model_.items.empty()){
		return;
	}
    if (!isSorted()){
		return;
	}
    auto lastIt = std::unique(deque_model_.items.begin(),deque_model_.items.end());
    if (lastIt!=deque_model_.items.end()){
        deque_model_.items.erase(lastIt,deque_model_.items.end());
    }

    resetIterator();
    ApplyModel();
}


void MainWindow::on_pb_reverse_clicked()
{
    if (deque_model_.items.empty()){
		return;
	}
    std::reverse(deque_model_.items.begin(), deque_model_.items.end());
    ApplyModel();
}


void MainWindow::on_pb_shuffle_clicked()
{
    if (deque_model_.items.empty()){
		return;
	}
    std::shuffle(deque_model_.items.begin(),deque_model_.items.end(),gen_shuffle_);
    ApplyModel();
}

void MainWindow::on_pb_lbound_clicked()
{
    if (deque_model_.items.empty()){
		return;
	}
    if (!isSorted()){
		return;
	}
    auto it = std::lower_bound(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = it;
    ApplyIterator();
}


void MainWindow::on_pb_ubound_clicked()
{
    if (deque_model_.items.empty()){
		return;
	}
    if (!isSorted()){
		return;
	}
    auto it = std::upper_bound(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = it;
    ApplyIterator();
}

