#include "lessonview.h"
#include "mergedhorizontalheader.h"
#include "ui_lessonview.h"
#include "start_lesson.h"
#include "QSqlError"
#include "aboutlesson.h"
#include "mergedheader.h"

#include <QPainter>
#include <QPdfWriter>
#include <QPrinter>
#include <QRegExp>

#include <QPrintPreviewDialog>
#include <QScreen>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QFileDialog>
#include <QPrintDialog>
#include <QCloseEvent>

LessonView::LessonView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LessonView)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(13);
    ui->tableWidget->setRowCount(14);

    for(int i = 0; i<ui->tableWidget->rowCount(); i++)
    {
        for(int j = 0; j<ui->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem();
            ui->tableWidget->setItem(i,j,item);
        }
    }

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);

    ui->tableWidget->item(0,1)->setText("Понедельник");
    ui->tableWidget->item(0,1)->setTextAlignment(Qt::AlignCenter);

    ui->tableWidget->item(0,3)->setText("Вторник");
    ui->tableWidget->item(0,3)->setTextAlignment(Qt::AlignCenter);

    ui->tableWidget->item(0,5)->setText("Среда");
    ui->tableWidget->item(0,5)->setTextAlignment(Qt::AlignCenter);

    ui->tableWidget->item(0,7)->setText("Четверг");
    ui->tableWidget->item(0,7)->setTextAlignment(Qt::AlignCenter);

    ui->tableWidget->item(0,9)->setText("Пятница");
    ui->tableWidget->item(0,9)->setTextAlignment(Qt::AlignCenter);

    ui->tableWidget->item(0,11)->setText("Суббота");
    ui->tableWidget->item(0,11)->setTextAlignment(Qt::AlignCenter);

    // Запрет редактирования ячеек в конкретной строке
    int rowToDisable = 0;
    for (int column = 0; column < ui->tableWidget->columnCount(); ++column)
    {
        QTableWidgetItem* item = ui->tableWidget->item(rowToDisable, column);
        if (item)
        {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
    }

    // Запрет редактирования ячеек в конкретном столбце
    int columnToDisable = 0;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        QTableWidgetItem* item = ui->tableWidget->item(row, columnToDisable);
        if (item)
        {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
    }

    QString text = "Строка 1\nСтрока 2\nСтрока 3";

    ui->tableWidget->item(1,1)->setText(text);

    // Настройка для отображения многстрочного текста
    ui->tableWidget->item(1,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // альтернативно


    // QFontMetrics metrics(item->font());
    // int textHeight = metrics.height() * 4; // высота текста для 3 строк
    // ui->tableWidget->setRowHeight(1, textHeight);

    connect(ui->tableWidget, &QTableWidget::cellDoubleClicked, this, &LessonView::ClickedLeftButton);

    QSqlDatabase db;
    if (!connectToDatabase(db, "/home/elf/lesson/LessonView/lesson_base.db"))
        return;

    // Предположим, у вас есть указатель на QTableWidget в UI
    QTableWidget *tableWidget = ui->tableWidget;
    loadDataToTable(db, tableWidget);

    table = ui->tableWidget;  // например, связанный с ui
    str = "какой-то текст";        // или получение значения из другого места

    // Заменим horizontalHeader на наш кастомный
    MergedHeader *hdr = new MergedHeader(Qt::Horizontal, table);
    table->setHorizontalHeader(hdr);

    // если хотите заменить вертикальный заголовок (строки)
    MergedHorizontalHeader *vh = new MergedHorizontalHeader(Qt::Vertical, table);
    table->setVerticalHeader(vh);

    // Установим ширины секций, чтобы пример выглядел аккуратно
    for (int c = 0; c < 4; ++c)
        table->setColumnWidth(c, 100);

    connect(ui->lessonPrint, &QAction::triggered, this, [=](){
        printLessonDialog();
    });

    connect(ui->lessonPrintPreview, &QAction::triggered, this, [=](){
        showPrintPreview(parent, table, str);
    });

    ui->lessonLock->setCheckable(true);

    connect(ui->lessonNew, &QAction::triggered, this, &LessonView::newLesson);
    connect(ui->lessonSave, &QAction::triggered, this, &LessonView::saveLesson);
    connect(ui->lessonAbout, &QAction::triggered, this, &LessonView::aboutLessons);
    connect(ui->lessonLock, &QAction::triggered, this, &LessonView::notEditTable);
    connect(ui->tableWidget, &QTableWidget::itemChanged, this, &LessonView::onItemChanged);
    connect(ui->lessonOpen, &QAction::triggered, this, &LessonView::openLesson);
    connect(ui->lessonClose, &QAction::triggered, this, &LessonView::close);
    connect(ui->deleteLesson, &QAction::triggered, this, &LessonView::deleteLesson);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    setWindowTitle("Программатор нагрузки");
}

LessonView::~LessonView()
{
    delete ui;
}

void LessonView::deleteLesson()
{
    int row = table->currentRow();
    int column = table->currentColumn();
    if (row < 0 || column < 0) return;
    if (auto *it = table->item(row, column))
    {
        it->setText(QString());
    }
}

void LessonView::openLesson()
{
    QString filter = tr("Текстовые файлы (*.txt);;Все файлы (*)");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), QString(), filter);
    if (fileName.isEmpty()) return;

   // openFile(fileName);
}

void LessonView::closeEvent (QCloseEvent *event)
{
    if (!isModified)
    {
        event->accept();
        return;
    }

    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Сохранить изменения?"),
                                                           tr("Данные таблицы были изменены. Сохранить перед выходом?"),
                                                           QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                                           QMessageBox::Save);

    if (ret == QMessageBox::Save)
    {
        if (saveLesson())
        {
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
    else if (ret == QMessageBox::Discard)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void LessonView::onItemChanged()
{
    setWindowTitle("Программатор нагрузки" + QString("*"));
    isModified = true;
}

void LessonView::notEditTable(bool checked)
{
    editingEnabled = checked; // Устанавливаем состояние редактирования на основе состояния кнопки
    ui->tableWidget->setEditTriggers(editingEnabled ?
                                         QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed :
                                         QAbstractItemView::NoEditTriggers);

    if (editingEnabled)
    {
        table->clearSelection(); // Снимаем выделение
    }
}

void LessonView::printLessonDialog()
{
    // QPrinter printer; // Создаем объект принтера
    // QPrintDialog dialog(&printer, this); // Создаем диалог печати

    // dialog.setWindowTitle("Печать документа");

    // // Проверяем, нажал ли пользователь "ОК"
    // if (dialog.exec() == QDialog::Accepted)
    // {
    //     print_lesson(table,&printer);
    // }

    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPageSize::A4);

    QPageLayout layout(QPageSize(QPageSize::A4), QPageLayout::Landscape, QMarginsF(0,0,0,0), QPageLayout::Millimeter);
    printer.setPageLayout(layout);
    printer.setResolution(300);
    printer.setFullPage(true);

    QPrintDialog dlg(&printer, nullptr);
    dlg.setWindowTitle("Печать таблицы");
    if (dlg.exec() == QDialog::Accepted)
    {
        // При успешном выборе принтера/файла вызываем функцию печати
        bool ok = print_lesson(table, &printer);
        if (ok) qDebug() << "Печать выполнена";
        else qDebug() << "Ошибка печати";
    }
    else
    {
        qDebug() << "Печать отменена";
    }
}

void LessonView::aboutLessons()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    rsc3 = new aboutLesson(this);
    rsc3->setWindowTitle("О программе");
    rsc3->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            rsc3->size(),
            screen->geometry()));

    rsc3->exec();
}

bool LessonView::saveLesson()
{
    QSqlDatabase db = QSqlDatabase::database("connection1");

    if (!db.isOpen())
    {
        QMessageBox::critical(nullptr, "Ошибка", "База данных не открыта");
        return false;
    }

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        int id = ui->tableWidget->item(row, 0)->text().toInt();

        for (int col = 2; col < ui->tableWidget->columnCount(); ++col)
        {
            QTableWidgetItem* item = ui->tableWidget->item(row, col);
            if (item)
            {
                QString text = item->text().trimmed();

                // Если ячейка пуста — ничего не делаем
                if (text.isEmpty())
                {
                    continue;
                }

                // Проверка, что содержимое — только цифра
                QRegExp onlyDigitsRegex("^[0-9]+$");
                bool isNumber = onlyDigitsRegex.exactMatch(text);

                QString combinedText;

                if (isNumber)
                {
                    // Всё, что есть — цифра, сохраняем так
                    combinedText = text;
                }
                else
                {
                    // Иначе считаем, что внутри 3 строки (отображение)
                    // Пытаемся разбить по переносам
                    QStringList parts = text.split("\n");
                    QString part1, part2, part3, part4;

                    // Получаем каждую из трех частей, если есть
                    part1 = parts.size() > 0 ? parts.at(0) : "";
                    part2 = parts.size() > 1 ? parts.at(1) : "";
                    part3 = parts.size() > 2 ? parts.at(2) : "";
                    part4 = parts.size() > 3 ? parts.at(3) : "";


                    // Склеиваем через \n
                    combinedText = part1 + "\\n" + part2 + "\\n" + part3 + "\\n" + part4;
                }

                //qDebug() << combinedText;

                // Определяем название столбца
                QString columnName;
                switch (col) {
                case 1: columnName = "Понедельник"; break;
                case 2: columnName = "Вторник"; break;
                case 3: columnName = "Среда"; break;
                case 4: columnName = "Четверг"; break;
                case 5: columnName = "Пятница"; break;
                case 6: columnName = "Суббота"; break;
                default: continue; // пропускаем остальные
                }

                QSqlQuery query(db);
                query.prepare("SELECT COUNT(*) FROM Lessons WHERE id = :id");
                query.bindValue(":id", id);
                query.exec();

                bool rowExists = false;
                if (query.next()) {
                    rowExists = query.value(0).toInt() > 0;
                }

                db.transaction();

                if (rowExists) {
                    // Обновляем существующую
                    query.prepare(QString("UPDATE Lessons SET %1 = :content WHERE id = :id").arg(columnName));
                    query.bindValue(":id", id);
                } else {
                    // Вставляем новую
                    query.prepare(QString("INSERT INTO Lessons (id, %1) VALUES (:id, :content)").arg(columnName));
                    query.bindValue(":id", id);
                }

                //qDebug() << "Вставка текста" << combinedText;
                query.bindValue(":content", combinedText);

                if (!query.exec()) {
                    QMessageBox::critical(nullptr, "Ошибка базы данных",
                                          QString("Ошибка при сохранении ячейки (%1, %2): %3")
                                              .arg(row)
                                              .arg(col)
                                              .arg(query.lastError().text()));
                }
                db.commit();
            }
        }
    }

    QMessageBox::information(nullptr, "Успех", "Данные успешно сохранены");

    isModified = false;
    // убираем звёздочку
    QString t = windowTitle();
    if (t.endsWith("*")) t.chop(1);
    setWindowTitle(t);
    return true;
}

void LessonView::newLesson()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    rsc2 = new start_lesson(this);
    rsc2->setWindowTitle("Введите данные преподавателя");
    rsc2->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            rsc2->size(),
            screen->geometry()));

    //rsc->wf = this;
    rsc2->exec();
}

void LessonView::ClickedLeftButton(int row, int column)
{
    // if (editingEnabled)
    // {
    //     return; // Преждевременный выход, если редактирование запрещено
    // }
    // else
    // {
    //     QScreen *screen = QGuiApplication::primaryScreen();
    //     rsc = new Add_lesson(this);
    //     rsc->setWindowTitle("Введите данные для ячейки");
    //     rsc->setGeometry(
    //         QStyle::alignedRect(
    //             Qt::LeftToRight,
    //             Qt::AlignCenter,
    //             rsc->size(),
    //             screen->geometry()));

    //     rsc->exec();

    //     QString combinedText = rsc->text11 + "\n" + rsc->text22 + "\n" + rsc->text33 + "\n" + rsc->text44;
    //     ui->tableWidget->item(row, column)->setText(combinedText);

    //     // Проверяем существование ячейки
    //     if (!ui->tableWidget->item(row, column))
    //         ui->tableWidget->setItem(row, column, new QTableWidgetItem());

    //     auto item = ui->tableWidget->item(row, column);
    //     item->setText(combinedText);
    //     item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); // центрирование по горизонтали и вертикали
    //     ui->tableWidget->resizeRowsToContents();

    //     rsc->deleteLater(); // Удаляем диалог после закрытия
    //}
    if (editingEnabled)
        return;

    QScreen *screen = QGuiApplication::primaryScreen();
    rsc = new Add_lesson(this);
    rsc->setWindowTitle("Введите данные для ячейки");
    rsc->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            rsc->size(),
            screen->geometry()));

    // Выполняем диалог и проверяем результат
    if (rsc->exec() == QDialog::Accepted) {
        QString combinedText = rsc->text11 + "\n" + rsc->text22 + "\n" + rsc->text33 + "\n" + rsc->text44;

        if (!ui->tableWidget->item(row, column))
            ui->tableWidget->setItem(row, column, new QTableWidgetItem());

        auto item = ui->tableWidget->item(row, column);
        item->setText(combinedText);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->tableWidget->resizeRowsToContents();
    }

    rsc->deleteLater();
}

bool LessonView::connectToDatabase(QSqlDatabase &db, QString path)
{
    db = QSqlDatabase::addDatabase("QSQLITE", "connection1");
    db.setDatabaseName(path); // путь к вашей базе

    if (!db.open()) {
        qDebug() << "Ошибка подключения:" << db.lastError().text();
        return false;
    }
    qDebug() << "База подключена!";
    return true;
}

void LessonView::loadDataToTable(QSqlDatabase &db, QTableWidget *tableWidget)
{
    ui->tableWidget->setFont(QFont("Arial", 10));

    //QSqlQuery query(db);

    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return; // Exit if the database is not open
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM Lessons")) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return; // Exit on query failure
    }

    // Выполняем SELECT-запрос
    if (query.exec("SELECT * FROM Lessons"))
    {
        // Очищаем таблицу
        tableWidget->clear();

        // Получаем количество колонок
        int columnCount = query.record().count();
        //int totalColumns = columnCount;

        // Устанавливаем число колонок
        tableWidget->setColumnCount(columnCount);

        // Получаем имена полей из базы для заголовков
        QStringList headers;
        for (int i = 0; i < columnCount; ++i) {
            headers << query.record().fieldName(i);
        }
        // Устанавливаем горизонтальные заголовки
        tableWidget->setHorizontalHeaderLabels(headers);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->verticalHeader()->setVisible(true);

        // Установка количества строк
        tableWidget->setRowCount(0);

        int currentRow = 0;
        // Заполняем таблицу данными
        while (query.next())
        {
           tableWidget->insertRow(currentRow);
           // int currentColumn = 0;
            for (int col = 0; col < columnCount; ++col)
            {
               QString originalValue = query.value(col).toString(); // Данные из базы
              // qDebug() << "Значение из базы:" << originalValue;

               originalValue.replace("\\n", "\n");  // заменить буквы '\\n' на перенос строки
              // qDebug() << "Значение из базы2:" << originalValue;

               QStringList parts = originalValue.split('\n');
               QString text1, text2, text3, text4;
               QString displayText;
               if (parts.size() == 4)
               {
                   // Есть ровно три части — можно их использовать или обработать
                   text1 = parts.at(0);
                   text2 = parts.at(1);
                   text3 = parts.at(2);
                   text4 = parts.at(3);

                   // Пример использования:
                   displayText = text1 + "\n" + text2 + "\n" + text3 + "\n" + text4;
                }
               else if (parts.size() == 1 && !parts.at(0).isEmpty())
               {
                   // Только один непустой фрагмент — оставить содержимое без изменений
                   QString finalValue = originalValue;
                   displayText = finalValue;
                   // Используйте finalValue далее по необходимости


               } else
               {
                   // Все остальные случаи — оставить как есть или обработать по необходимости
                   QString finalValue = originalValue;
                   displayText = finalValue;
                   //qDebug() << "Разделенные части:" << parts;
               }

               //qDebug() << "Разделенные части:" << displayText;


               QStringList nonEmptyParts;
               // for (const auto &part : parts)
               // {
               //     if (!part.isEmpty())
               //     {
               //         nonEmptyParts << part;
               //     }
               // }

               for (int i = 0; i < parts.size(); ++i)
               {
                   const QString &part = parts[i];
                   if (!part.isEmpty())
                   {
                       nonEmptyParts << part;
                   }
               }

               //QString displayText;
               if (!nonEmptyParts.isEmpty()) {
                   displayText = nonEmptyParts.join("\n"); // или любой разделитель
               } else {
                   displayText = ""; // или "Пусто"
               }

               // Заполняем существующую ячейку
               QTableWidgetItem *item = ui->tableWidget->item(currentRow, col);
               if (!item)
               {
                   item = new QTableWidgetItem();
                   ui->tableWidget->setItem(currentRow, col, item);
               }
               item->setText(displayText);
               item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
           }
            ui->tableWidget->setVerticalHeaderItem(currentRow, new QTableWidgetItem(QString::number(currentRow + 1)));

           ++currentRow;
        }
    } else
    {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    }

    // Предположим, у вас есть таблица с N строками
    int rowCount = ui->tableWidget->rowCount();

    // Массив данных для вертикальных заголовков
    QStringList verticalHeaders = {"8.30-10.05\nВерхняя неделя", "8.30-10.05\nНижняя неделя",
                                   "10.25-12.00\nВерхняя неделя", "10.25-12.00\nНижняя неделя",
                                   "12.30-14.05\nВерхняя неделя", "12.30-14.05\nНижняя неделя",
                                   "14.20-15.55\nВерхняя неделя", "14.20-15.55\nНижняя неделя",
                                   "16.05-17.40\nВерхняя неделя", "16.05-17.40\nНижняя неделя",
                                   "17.50-19.20\nВерхняя неделя", "17.50-19.20\nНижняя неделя",
                                   "19.25-21.10\nВерхняя неделя", "19.25-21.10\nНижняя неделя"};

    // Убедитесь, что количество элементов в verticalHeaders совпадает с количеством строк
    Q_ASSERT(verticalHeaders.size() >= rowCount);

    for (int row = 0; row < rowCount; ++row)
    {
        //ui->tableWidget->setVerticalHeaderItem(row, new QTableWidgetItem(verticalHeaders.at(row)));

        QTableWidgetItem *hi = new QTableWidgetItem(verticalHeaders.at(row));
        hi->setTextAlignment(Qt::AlignCenter);
        // Разрешаем перенос строк в тексте (в заголовках QTableWidgetItem это учитывается автоматически)
        ui->tableWidget->setVerticalHeaderItem(row, hi);
    }

    // Увеличим высоту строки заголовка (высоту строки таблицы), чтобы поместился многострочный заголовок
    for (int row = 0; row < rowCount; ++row)
    {
        ui->tableWidget->setRowHeight(row, 50); // подберите нужное значение
    }

    for (int col = 0; col < tableWidget->columnCount(); ++col)
    {
        QString headerText = tableWidget->horizontalHeaderItem(col)->text();
        if (headerText == "id")
        { // замените на точное имя заголовка
            tableWidget->hideColumn(col);
            break;
        }
    }

    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->viewport()->update(); // попробуйте добавить

}

bool LessonView::print_lesson(QTableWidget *table, QPrinter *printer)
{
    if (!table || !printer) return false;

    int logicalW = table->verticalHeader()->width();
    for (int c = 0; c < table->model()->columnCount(); ++c)
        logicalW += table->columnWidth(c);

    // Добавляем ширину вертикальных линий сетки
    logicalW += table->model()->columnCount() * table->gridStyle();

    // Добавляем дополнительный отступ справа
    logicalW += 30;

    int logicalH = table->horizontalHeader()->height();
    for (int r = 0; r < table->model()->rowCount(); ++r)
        logicalH += table->rowHeight(r);

    // Добавляем высоту горизонтальных линий сетки
    logicalH += (table->model()->rowCount() + 1) * table->gridStyle();

    // Добавляем дополнительный отступ снизу (например, 30 пикселей)
    logicalH += 30;

    // Добавляем высоту горизонтальных линий сетки

    if (logicalW <= 0 || logicalH <= 0) return false;

    // --- paper rect in device pixels ---
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
    QRectF paperRect = printer->paperRect(QPrinter::DevicePixel);
#else
    QRectF paperRect = QRectF(printer->paperRect(QPrinter::DevicePixel));
#endif

    // margins and limits
    const int innerPad = 8;    // top/bottom small pad
    const int marginPx = 16;   // left/right small margin
    const int maxDeviceDim = 16000;

    // available area inside paper (device pixels)
    qreal availW = qMax<qreal>(1.0, paperRect.width() - 2.0 * marginPx);
    qreal availH = qMax<qreal>(1.0, paperRect.height() - 2.0 * innerPad);

    // candidate target sizes for intermediate image
    int targetW = int(std::floor(availW + 0.5));
    int targetH = int(std::floor(availH + 0.5));

    qreal downscale = 1.0;
    if (targetW > maxDeviceDim || targetH > maxDeviceDim) {
        qreal sx = qreal(maxDeviceDim) / qMax(targetW, 1);
        qreal sy = qreal(maxDeviceDim) / qMax(targetH, 1);
        downscale = qMin(sx, sy);
        targetW = qMax(1, int(targetW * downscale));
        targetH = qMax(1, int(targetH * downscale));
    }

    // compute renderScale so X and Y use same scale
    qreal sx = qreal(targetW) / qMax<qreal>(1.0, logicalW);
    qreal sy = qreal(targetH) / qMax<qreal>(1.0, logicalH);
    qreal renderScale = qMin(sx, sy);
    if (renderScale <= 0) renderScale = 1.0;

    // create device image exactly logical * renderScale (rounded)
    int imgW = qMax(1, int(std::floor(logicalW * renderScale + 0.5)));
    int imgH = qMax(1, int(std::floor(logicalH * renderScale + 0.5)));

    // ensure within device limits
    if (imgW > maxDeviceDim || imgH > maxDeviceDim) {
        qreal s = qMin(qreal(maxDeviceDim) / imgW, qreal(maxDeviceDim) / imgH);
        imgW = qMax(1, int(imgW * s));
        imgH = qMax(1, int(imgH * s));
    }

    QImage deviceImg(imgW, imgH, QImage::Format_ARGB32);
    deviceImg.setDevicePixelRatio(1);
    deviceImg.fill(Qt::white);

    qDebug() << "logicalW,logicalH:" << logicalW << logicalH
             << "imgW,imgH:" << imgW << imgH
             << "renderScale:" << renderScale
             << "targetW,targetH:" << targetW << targetH;

    // render table into deviceImg with the SAME scale for X and Y, no translation
    {
        // Сохраняем оригинальные стили
        QString originalHorizontalStyle = table->horizontalHeader()->styleSheet();
        QString originalVerticalStyle = table->verticalHeader()->styleSheet();

        // Создаем белую палитру
        QPalette whitePalette;
        whitePalette.setColor(QPalette::Base, Qt::white);
        whitePalette.setColor(QPalette::Window, Qt::white);
        whitePalette.setColor(QPalette::AlternateBase, Qt::white);
        whitePalette.setColor(QPalette::Text, Qt::black);

        // Применяем к заголовкам
        table->horizontalHeader()->setPalette(whitePalette);
        table->verticalHeader()->setPalette(whitePalette);


        QPainter devicePainter(&deviceImg);
        devicePainter.setRenderHint(QPainter::TextAntialiasing, true);
        devicePainter.setRenderHint(QPainter::Antialiasing, true);
        devicePainter.setRenderHint(QPainter::SmoothPixmapTransform, true);

        devicePainter.save();
        devicePainter.scale(renderScale, renderScale);
        QRect fullLogicalRect(0, 0, logicalW, logicalH);
        table->render(&devicePainter, QPoint(0, 0), QRegion(fullLogicalRect), QWidget::DrawChildren);
        devicePainter.restore();
        devicePainter.end();

        // Восстанавливаем оригинальные стили
        //table->horizontalHeader()->setStyleSheet(originalHorizontalStyle);
        //table->verticalHeader()->setStyleSheet(originalVerticalStyle);
    }

    deviceImg.save("output.jpg", nullptr, 90);

    // draw deviceImg into printer, scaled to fit avail area and centered with small margins
    QPainter painter(printer);
    if (!painter.isActive()) {
        qWarning() << "Failed to activate painter for printer";
        return false;
    }
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHints(QPainter::Antialiasing
                           | QPainter::TextAntialiasing);


    // compute scale to fit into available paper area (preserve aspect ratio)
    qreal fitScale = qMin(availW / deviceImg.width(), availH / deviceImg.height());
    if (fitScale <= 0) fitScale = 1.0;

    qreal finalW = std::floor(deviceImg.width() * fitScale + 0.5);
    qreal finalH = std::floor(deviceImg.height() * fitScale + 0.5);

    // center inside paper while leaving small margins
    qreal startX = paperRect.x() + (paperRect.width() - finalW) / 2.0;
    qreal startY = paperRect.y() + (paperRect.height() - finalH) / 2.0;
    qreal drawX = std::floor(startX + 0.5);
    qreal drawY = std::floor(startY + 0.5);

    // clamp to paper bounds
    qreal rightLimit = paperRect.x() + paperRect.width();
    qreal bottomLimit = paperRect.y() + paperRect.height();
    if (drawX + finalW > rightLimit) finalW = rightLimit - drawX;
    if (drawY + finalH > bottomLimit) finalH = bottomLimit - drawY;
    if (finalW < 1) finalW = 1;
    if (finalH < 1) finalH = 1;

    QRectF finalDst(drawX, drawY, finalW, finalH);
    QRectF srcRect(0.0, 0.0, qreal(deviceImg.width()), qreal(deviceImg.height()));

    qDebug() << "paperRect:" << paperRect.size()
             << "deviceImg:" << deviceImg.size()
             << "finalDst:" << finalDst
             << "srcRect:" << srcRect
             << "drawX+finalW:" << drawX + finalW << "rightLimit:" << rightLimit;

    painter.drawImage(finalDst, deviceImg, srcRect);
    painter.end();

    return true;
}

void LessonView::showPrintPreview(QWidget* parent, QTableWidget* table, const QString& str)
{
    QPrintPreviewDialog *previewDialog = new QPrintPreviewDialog(parent);
    connect(previewDialog, &QPrintPreviewDialog::paintRequested, [=](QPrinter *printer) {
        printer->setPageSize(QPageSize::A4);
        QPageLayout pageLayout;
        pageLayout.setOrientation(QPageLayout::Landscape);
        printer->setPageLayout(pageLayout);

        // Вызываем функцию для рисования содержимого таблицы
        print_lesson(table,printer); // Передаем printer и другие параметры
    });

    previewDialog->exec();
}
