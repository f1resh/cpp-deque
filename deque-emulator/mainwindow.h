#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QListWidgetItem>

#include <random>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetRandomGen(const std::mt19937& random_gen);

private slots:
    void on_pb_popfront_clicked();
    void on_pb_pushfront_clicked();
    void on_pb_popback_clicked();
    void on_pb_pushback_clicked();
    void on_pb_clear_clicked();
    void on_pb_tea_clicked();
    void on_pb_cakes_clicked();
    void on_pb_edit_clicked();
    void on_pb_erase_clicked();
    void on_pb_insert_clicked();
    void on_pb_minusminus_clicked();
    void on_pb_plusplus_clicked();
    void on_pb_begin_clicked();
    void on_pb_end_clicked();

    void on_list_widget_currentRowChanged(int currentRow);
    void on_pb_resize_clicked();
    void on_pb_find_clicked();
    void on_pb_maxelem_clicked();
    void on_pb_minelem_clicked();
    void on_pb_count_clicked();
    void on_pb_sort_clicked();
    void on_pb_sort2_clicked();
    void on_pb_unique_clicked();
    void on_pb_reverse_clicked();
    void on_pb_shuffle_clicked();
    void on_pb_lbound_clicked();
    void on_pb_ubound_clicked();




private:
    void ApplyModel();
    void ApplyIterator();
    void resetIterator();
    bool isSorted();

private:
    Model deque_model_;
    Ui::MainWindow *ui;
    std::mt19937 gen_shuffle_;
};
