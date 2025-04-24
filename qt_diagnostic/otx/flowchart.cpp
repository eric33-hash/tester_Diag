#include "flowchart.h"


FlowChart::FlowChart(QWidget *parent, Qt::WindowFlags f) : QWidget(parent,f)
{
    this->grabKeyboard();
//    installEventFilter(this);
    initVar();
    setMouseTracking(true);
    update();
}

void FlowChart::initVar()
{
    mouseEventType = MOUSE_EVENT_TYPE::NONE;
    curPaintChart = nullptr;
    curSelecChart = nullptr;
    newLineChart = nullptr;
    newLineFromSelectChart = nullptr;
    newLineToSelectChart = nullptr;
}

void FlowChart::resetFlowChartPanel()
{
    Chart_Base::resetStaticVal();
    curPaintChart = nullptr;
    curPaintChartType = PaintChartType::NONE;
    curSelecChart = nullptr;
    curSelecChartPos = QPoint();
    newLineChart = nullptr;
    newLineToSelectChart = nullptr;
    newLineFromSelectChart = nullptr;
    magPointDirect = ORIENTION::NONE;
    magPointFromIndex = 0;
    magPointToIndex = 0;
    sizePointDirect = ORIENTION::NONE;
    clearChartsLine();
    charts.reserve(0);
    charts.resize(0);
    line.reserve(0);
    line.resize(0);
    mouseEventType = MOUSE_EVENT_TYPE::NONE;
    fileIsOpened = false;
    fileIsSaved = true;
    filePath = "";
    setFileNameShow(fileIsSaved);
}

void FlowChart::setFileSetSaved(bool isSaved)
{
    if(fileIsSaved != isSaved)
    {
        fileIsSaved = isSaved;
        setFileNameShow(fileIsSaved);
    }
}

void FlowChart::setFileNameShow(bool isSaved)
{
    QString tmp;
    if(fileIsOpened)
    {
        tmp = QString("%1%2").arg(filePath).arg((isSaved?"":" *"));
        emit updateWindowTitle(tmp);
    }else
    {
        tmp = QString("%1%2").arg("Untitle").arg((isSaved?"":" *"));
        emit updateWindowTitle(tmp);
    }
}

Chart_Base * FlowChart::getCurPaintChart()
{
    return curPaintChart;
}

void FlowChart::setSelChartLineColor(const QColor &color)
{
    curSelecChart->paintChartDrawPen.setColor(color);
    curSelecChart->update();
}

void FlowChart::setSelChartFillColor(const QColor &color)
{
    curSelecChart->paintChartFillPen.setColor(color);
    curSelecChart->update();
}

void FlowChart::setMousePressedFlag(MOUSE_EVENT_TYPE f)
{
    mouseEventType = f;
}

void FlowChart::setPaintChart()
{
    if(curPaintChart != nullptr)
        delete curPaintChart;

    switch(curPaintChartType)
    {
        case PaintChartType::RECT:
        {
            curPaintChart = new Chart_Rect(this);
        }break;
        case PaintChartType::DIAMOND:
        {
            curPaintChart = new Chart_Diamond(this);
        }break;
        case PaintChartType::ROUNDRECT:
        {
            curPaintChart = new Chart_RoundRect(this);
        }break;
        case PaintChartType::ELLIPSE:
        {
            curPaintChart = new Chart_Ellipse(this);
        }break;
        case PaintChartType::LINE:
        {
            curPaintChart = new Chart_Line(this);
        }break;
        case PaintChartType::TRAPEZOID:
        {
            curPaintChart = new Chart_Trapezoid(this);
        }break;
        default:case PaintChartType::NONE:{
            curPaintChart = nullptr;
        }break;
    }
    if(curPaintChart)
    {
        mouseEventType = MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE;
    }
}

void FlowChart::setPaintChart(QString data)
{
    if(curPaintChart != nullptr)
        delete curPaintChart;

    switch(curPaintChartType)
    {
        case PaintChartType::RECT:
        {
            curPaintChart = new Chart_Rect(data,this);
        }break;
        case PaintChartType::DIAMOND:
        {
            curPaintChart = new Chart_Diamond(data,this);
        }break;
        case PaintChartType::ROUNDRECT:
        {
            curPaintChart = new Chart_RoundRect(this);
        }break;
        case PaintChartType::ELLIPSE:
        {
            curPaintChart = new Chart_Ellipse(this);
        }break;
        case PaintChartType::LINE:
        {
            curPaintChart = new Chart_Line(this);
        }break;
        case PaintChartType::TRAPEZOID:
        {
            curPaintChart = new Chart_Trapezoid(this);
        }break;
        default:case PaintChartType::NONE:{
            curPaintChart = nullptr;
        }break;
    }
    if(curPaintChart)
    {
        mouseEventType = MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE;
    }
}


void FlowChart::setSelecChart(Chart_Base * cb, int x, int y)
{

    emit disableStyle();
    this->grabKeyboard();
    if(curSelecChart != nullptr) curSelecChart->hideMagSize();
    curSelecChart = cb;
    curSelecChart->showMagSize();
    curSelecChartPos = QPoint(x,y);
    mouseEventType = MOUSE_EVENT_TYPE::RUNTIME_CHANGE_POS;
    Chart_Line *cl = nullptr;
    if(nullptr == (cl = dynamic_cast<Chart_Line*>(cb)))
    {
        emit sendChartStyle(cb->paintChartDrawPen,cb->paintChartFillPen);
    }else
    {
        emit sendLineStyle(cl->paintChartDrawPen,cl->getStartLineHeadType(),cl->getEndLineHeadType());
    }
}

bool FlowChart::openChartFile(QString path)
{
    otx.load(path);

    struct diagnsoticCommand* current = otx.getSequenceData();
    QPoint centerGetY(0,0);
    int xxxx= 0;
    int yyyy = 1;
    while (current)
    {

        if(strcmp(current->m_seq.type , "action") == 0)
        {
              centerGetY = paintrect(QString(QString(current->xsi_type) + "-"+ QString(current->m_seq.data)),0,centerGetY.y() + 10);
              xxxx = charts.size();
              if(charts.size() > 1)
              {
                  paintline(charts[yyyy-1],charts[xxxx-1],ORIENTION::SOUTH);
                  yyyy = xxxx;
              }
        }

        else if(strcmp(current->m_seq.type , "branch") == 0)
        {
            centerGetY = paintdia(QString(QString(current->xsi_type) + "-"+ QString(current->m_seq.data)),0,centerGetY.y() + 10);
            xxxx = charts.size();
            if(charts.size() > 1)
            {
                paintline(charts[charts.size()-2],charts[charts.size()-1],ORIENTION::SOUTH);
                yyyy = xxxx;
            }
            //paintline(charts[charts.size() - 2],charts[charts.size() - 1],ORIENTION::SOUTH);
            if(current->conditionalCommand != NULL)
            {
                struct diagnsoticCommand* conditionflow = current->conditionalCommand;
                QPoint centerGetYSub(centerGetY.x(),centerGetY.y());
                bool anter = false,paint = false;
                while(conditionflow)
                {
                    if(strcmp(conditionflow->m_seq.type,"action") == 0)
                    {
                        if(anter == false)
                        {
                            centerGetYSub = paintrect(QString(QString(conditionflow->xsi_type) + "-"+ QString(conditionflow->m_seq.data)),500,centerGetYSub.y() -85);
                            paintline(charts[charts.size() - 2],charts[charts.size() - 1],ORIENTION::EAST);
                            anter = true;
                        }
                        else
                        {
                            paint = true;
                            centerGetYSub = paintrect(QString(QString(conditionflow->xsi_type) + "-"+ QString(conditionflow->m_seq.data)),500,centerGetYSub.y()+ 10);
                            paintline(charts[charts.size() - 2],charts[charts.size() - 1],ORIENTION::SOUTH);
                        }

                        if(conditionflow->nextcommand != NULL && paint)
                        {
                        }
                    }
                    conditionflow = conditionflow->nextcommand;
                }
            }
        }

        else if(strcmp(current->m_seq.type , "loop") == 0)
        {
            centerGetY = paintdia(QString(QString(current->xsi_type) + "-"+ QString(current->m_seq.data)),0,centerGetY.y() + 10);
            xxxx = charts.size();
            if(charts.size() > 1)
            {
                paintline(charts[charts.size()-2],charts[charts.size()-1],ORIENTION::SOUTH);
                yyyy = xxxx;
            }
             int branchSize = 0;
            if(current->conditionalCommand != NULL)
            {
                struct diagnsoticCommand* conditionflow = current->conditionalCommand;
                QPoint centerGetYSubLoop(centerGetY.x(),centerGetY.y());
                int anterloop = 0;
                int zzz = yyyy;
                int  arrow = charts.size();

                while(conditionflow)
                {
                    if(strcmp(conditionflow->m_seq.type,"action") == 0)
                    {
                        centerGetYSubLoop = paintrect(QString(QString(conditionflow->xsi_type) + "-"+ QString(conditionflow->m_seq.data)),0,centerGetYSubLoop.y());
                        paintline(charts[zzz - 1],charts[charts.size()-1],ORIENTION::SOUTH);
                        zzz = charts.size();
                        if(conditionflow->nextcommand != NULL)
                        {

                        }
                    }
                    else if(strcmp(conditionflow->m_seq.type , "branch") == 0)
                    {
                        centerGetYSubLoop = paintdia(QString(QString(conditionflow->xsi_type) + "-"+ QString(conditionflow->m_seq.data)),0,centerGetYSubLoop.y() );
                        paintline(charts[zzz - 1],charts[charts.size()-1],ORIENTION::SOUTH);
                         zzz = charts.size();
                        if(conditionflow->conditionalCommand != NULL)
                        {
                            branchSize = charts.size();
                            QPoint loopSub(centerGetYSubLoop.x(),centerGetYSubLoop.y());
                            bool loopantersub = false;
                            struct diagnsoticCommand* conditionflowsub = conditionflow->conditionalCommand;
                            int lastarrow = zzz;
                            while(conditionflowsub)
                            {
                                if(strcmp(conditionflowsub->m_seq.type,"action") == 0)
                                {
                                    if(loopantersub == false)
                                    {
                                        loopSub = paintrect(QString(QString(conditionflowsub->xsi_type) + "-"+ QString(conditionflowsub->m_seq.data)),500 + anterloop* 500,loopSub.y() -80);
                                        paintline(charts[charts.size() - 2],charts[charts.size() - 1],ORIENTION::EAST);
                                        loopantersub = true;
                                    }
                                    else
                                    {
                                        loopSub = paintrect(QString(QString(conditionflowsub->xsi_type) + "-"+ QString(conditionflowsub->m_seq.data)),500 + anterloop* 500,loopSub.y() );
                                        paintline(charts[charts.size() - 2],charts[charts.size() - 1],ORIENTION::SOUTH);
                                    }
                                    if(conditionflowsub->nextcommand != NULL)
                                    {

                                    }
                                }
                                if(strcmp(conditionflowsub->m_seq.type,"branch") == 0)
                                {
                                    if(loopantersub == false)
                                    {
                                        loopSub = paintdia(QString(QString(conditionflowsub->xsi_type) + "-"+ QString(conditionflowsub->m_seq.data)),500 + anterloop* 500,loopSub.y() -80);
                                        paintline(charts[charts.size() - 2],charts[charts.size() - 1],ORIENTION::EAST);
                                        lastarrow = charts.size();
                                        loopantersub = true;
                                    }
                                    else
                                    {
                                        loopSub = paintdia(QString(QString(conditionflowsub->xsi_type) + "-"+ QString(conditionflowsub->m_seq.data)),500 + anterloop* 500,loopSub.y() );
                                        paintline(charts[lastarrow - 1],charts[charts.size() - 1],ORIENTION::SOUTH);
                                        lastarrow = charts.size();
                                    }
                                    if(conditionflowsub->nextcommand != NULL)
                                    {

                                    }
                                   struct diagnsoticCommand* conditionflowlast =  conditionflowsub->conditionalCommand;
                                   int anterlooplast = 1;
                                   QPoint lastloop(loopSub.x(),loopSub.y());
                                   bool loopantersublast = false;
                                   while(conditionflowlast)
                                   {
                                       if(strcmp(conditionflowlast->m_seq.type,"action") == 0)
                                       {
                                           if(loopantersublast == false)
                                           {
                                               lastloop = paintrect(QString(QString(conditionflowlast->xsi_type) + "-"+ QString(conditionflowlast->m_seq.data)),500 + anterloop* 500 + anterlooplast * 500,lastloop.y() -80);
                                               paintline(charts[charts.size() - 2],charts[charts.size() - 1],ORIENTION::EAST);
                                               loopantersublast = true;
                                           }
                                           else
                                           {
                                               lastloop = paintrect(QString(QString(conditionflowlast->xsi_type) + "-"+ QString(conditionflowlast->m_seq.data)),500 + anterloop* 500+ anterlooplast * 500,lastloop.y() );
                                               paintline(charts[charts.size() - 2],charts[charts.size() - 1],ORIENTION::SOUTH);
                                           }
                                           if(conditionflowsub->nextcommand != NULL)
                                           {

                                           }
                                       }
                                       if(strcmp(conditionflowlast->m_seq.type,"branch") == 0)
                                       {
                                           if(loopantersublast == false)
                                           {
                                               loopSub = paintdia(QString(QString(conditionflowlast->xsi_type) + "-"+ QString(conditionflowlast->m_seq.data)),500 + anterloop* 500+ anterlooplast * 500,lastloop.y()-95);
                                               paintline(charts[charts.size() - 2],charts[charts.size() - 1],ORIENTION::EAST);
                                               loopantersublast = true;
                                           }
                                           else
                                           {
                                               loopSub = paintdia(QString(QString(conditionflowlast->xsi_type) + "-"+ QString(conditionflowlast->m_seq.data)),500 + anterloop* 500+ anterlooplast * 500,lastloop.y());
                                               paintline(charts[charts.size() - 2],charts[charts.size() - 1],ORIENTION::SOUTH);
                                           }
                                           if(conditionflowsub->nextcommand != NULL)
                                           {

                                           }
                                       }
                                     conditionflowlast = conditionflowlast->nextcommand;
                                   }
                                   anterlooplast++;
                                }
                                conditionflowsub = conditionflowsub->nextcommand;
                            }
                            anterloop++;
                        }
                        branchSize = charts.size();
                    }
                    conditionflow = conditionflow->nextcommand;
                }
            }
        }
        current = current->nextcommand;

    }

    return true;
}

QPoint FlowChart::paintrect(QString data,int in_width,int in_height)
{
    curPaintChartType = PaintChartType::RECT;
    QGraphicsTextItem *textItem;
    textItem = new QGraphicsTextItem(data);
    int height = 0;
    if(textItem->boundingRect().width() <= 400)
    {
        curPaintChart = new Chart_Rect(470 - (textItem->boundingRect().width())/2.0 - 10 + in_width , in_height + 60  , textItem->boundingRect().width() + 20,60,data,this);
    }
    else
    {
        textItem->setTextWidth(400);
        curPaintChart = new Chart_Rect(260+ in_width,in_height + 60, 420, textItem->boundingRect().height() + 30,data,this);
        height = textItem->boundingRect().height() + 10;
    }

    mouseEventType = MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE;
    if(curSelecChart) curSelecChart->hideMagSize();
    curSelecChart = curPaintChart;
    curPaintChart->setXY(curPaintChart->pos().x(),curPaintChart->pos().y());

    if(curPaintChart->chartType == PaintChartType::LINE)
    {
        connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
        connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
        addLine(curPaintChart);
        Chart_Line *cl = dynamic_cast<Chart_Line*>(curSelecChart);
        emit sendLineStyle(cl->paintChartDrawPen,cl->getStartLineHeadType(),cl->getEndLineHeadType());
    }else
    {
        connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
        connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
        connect(curPaintChart,SIGNAL(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)),this,SLOT(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)));
        addChart(curPaintChart);
        emit sendChartStyle(curSelecChart->paintChartDrawPen,curSelecChart->paintChartFillPen);
    }

    curPaintChart->updateWidgetPosInof();
    curPaintChart->updatePaintInfo();
    curPaintChart->updateSizePointInfo();
    curPaintChart->updateSizePointPath();
    curPaintChart->updateMagPointInfo();
    curPaintChart->updateMagPointPath();
    curPaintChart->updateMagPointLine();
    curPaintChart->update();
    curPaintChart->show();
    mouseEventType = MOUSE_EVENT_TYPE::NONE;
    qDebug() << "y1 = " << curPaintChart->getMagiPointAbsY(0);
    qDebug() << "y2 = " << curPaintChart->getMagiPointAbsY(5);
    QPoint returnPoint(curPaintChart->getMagiPointAbsY(0),curPaintChart->getMagiPointAbsY(5));
    curPaintChart = nullptr;
    //paintline(curPaintChart,QPoint(curPaintChart->getMagiPointAbsX(2),curPaintChart->getMagiPointAbsY(2)),QPoint(curPaintChart->getMagiPointAbsX(2),curPaintChart->getMagiPointAbsY(2) + 60));
    return returnPoint;

}

QPoint FlowChart::paintdia(QString data,int in_width,int in_height)
{
    curPaintChartType = PaintChartType::DIAMOND;
    QGraphicsTextItem *textItem;
    textItem = new QGraphicsTextItem(data);
    int height = 0;
    if(textItem->boundingRect().width() <= 400)
    {
        curPaintChart = new Chart_Diamond(470 - textItem->boundingRect().width()/2.0 - 10 + in_width, in_height + 60  , textItem->boundingRect().width() +  20,40,data,this);
        qDebug() << "x = " << curPaintChart->getMagiPointAbsX(0);
    }
    else
    {
        textItem->setTextWidth(400);
        curPaintChart = new Chart_Rect(260+ in_width,in_height + 60, 420, textItem->boundingRect().height() + 10,data,this);
        height = textItem->boundingRect().height() + 10;
    }

    mouseEventType = MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE;
    if(curSelecChart) curSelecChart->hideMagSize();
    curSelecChart = curPaintChart;
    curPaintChart->setXY(curPaintChart->pos().x(),curPaintChart->pos().y());
//    curPaintChart->updateWidgetPosInof();
//    curPaintChart->updatePaintInfo();
//    curPaintChart->updateSizePointInfo();
//    curPaintChart->updateSizePointPath();
//    curPaintChart->updateMagPointInfo();
//    curPaintChart->updateMagPointPath();
//    curPaintChart->updateMagPointLine();


    if(curPaintChart->chartType == PaintChartType::LINE)
    {
        connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
        connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
        addLine(curPaintChart);
        Chart_Line *cl = dynamic_cast<Chart_Line*>(curSelecChart);
        emit sendLineStyle(cl->paintChartDrawPen,cl->getStartLineHeadType(),cl->getEndLineHeadType());
    }else
    {
        connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
        connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
        connect(curPaintChart,SIGNAL(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)),this,SLOT(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)));
        //connect(curPaintChart,SIGNAL(hideThisClass()),this,SLOT(resetSeletcChart()));
        addChart(curPaintChart);
        emit sendChartStyle(curSelecChart->paintChartDrawPen,curSelecChart->paintChartFillPen);
    }
    curPaintChart->update();
    curPaintChart->show();
    mouseEventType = MOUSE_EVENT_TYPE::NONE;
    QPoint returnPoint(curPaintChart->getMagiPointAbsY(0),curPaintChart->getMagiPointAbsY(2));
    curPaintChart = nullptr;
   // paintline(curPaintChart,QPoint(curPaintChart->getMagiPointAbsX(2),curPaintChart->getMagiPointAbsY(2)),QPoint(curPaintChart->getMagiPointAbsX(2),curPaintChart->getMagiPointAbsY(2) + 60));
    return returnPoint;
}

void FlowChart::paintline(Chart_Base* cbFrom,Chart_Base* cbTo,ORIENTION direct)
{
    switch (direct) {
        case ORIENTION::SOUTH:
        {
            if(cbFrom->getChartType() == PaintChartType::RECT)
            {
                magPointFromIndex = 5;
            }
            else if(cbFrom->getChartType() == PaintChartType::DIAMOND)
            {
                magPointFromIndex = 2;
            }
            if(cbTo->getChartType() == PaintChartType::RECT)
            {
                magPointToIndex = 1;
            }
            else if(cbTo->getChartType() == PaintChartType::DIAMOND)
            {
                magPointToIndex = 0;
            }
        }break;
    case ORIENTION::EAST:
    {
        if(cbFrom->getChartType() == PaintChartType::DIAMOND)
        {
            magPointFromIndex = 1;
        }
        if(cbTo->getChartType() == PaintChartType::RECT)
        {
            magPointToIndex = 7;
        }
        else if(cbTo->getChartType() == PaintChartType::DIAMOND)
        {
            magPointToIndex = 3;
        }
    }break;
        default:
            break;
    }

    if(newLineChart == nullptr)
    {
        newLineChart = new Chart_Line(this);
        if(curSelecChart)
            curSelecChart->hideMagSize();
        curSelecChart = newLineChart;
        addLine(newLineChart);
        //newLineChart->setAttribute(Qt::WA_StyledBackground,true);
        //newLineChart->setStyleSheet(QStringLiteral("background-color: rgb(100, 100, 100);"));
        connect(newLineChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
        connect(newLineChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
        newLineFromSelectChart = cbFrom;
   //     magPointFromIndex = 2;
        magPointDirect = direct;
        newLineChart->setXY(cbFrom->getMagiPointAbsX(magPointFromIndex),cbFrom->getMagiPointAbsY(magPointFromIndex));
        newLineChart->setStartChart(newLineFromSelectChart);
        newLineChart->setStartMagIndex(magPointFromIndex);
        newLineChart->setStartDirect(magPointDirect);
        newLineChart->update();
        newLineChart->show();

        cbFrom->addMagiPointStartLine(magPointFromIndex,newLineChart);
    }
    //magPointToIndex = 0;
    int x = cbTo->getMagiPointAbsX(magPointToIndex),y = cbTo->getMagiPointAbsY(magPointToIndex);

    for(auto it = charts.begin();it!=charts.end();it++)
    {
        //if(*it == newLineFromSelectChart) continue;
        if((*it)->autoSetMagi(x,y,magPointToIndex))
        {
            newLineToSelectChart = *it;
            break;
        }else{
            newLineToSelectChart = nullptr;
        }
    }
    //if(!newLineToSelectChart) newLineChart->resetEndChart();
    newLineChart->setWidthHeight(x,y,ORIENTION::ENDPOINT);
    newLineToSelectChart = cbTo;
    if(newLineToSelectChart)
    {
        newLineToSelectChart->addMagiPointEndLine(magPointToIndex,newLineChart);
        newLineToSelectChart->hideMagOnly();
        newLineChart->setEndChart(newLineToSelectChart);
        newLineChart->setEndMagIndex(magPointToIndex);
        newLineChart->setEndDirect(newLineToSelectChart->getMagiPointDirect(magPointToIndex));
        newLineChart->update();
    }else
    {
        if(newLineChart)
            newLineChart->resetEndChart();
    }
    mouseEventType = MOUSE_EVENT_TYPE::NONE;
    newLineChart = nullptr;
    newLineFromSelectChart = nullptr;
    newLineToSelectChart = nullptr;
    setFileSetSaved(false);
}

bool FlowChart::saveChartFile(ECU_SERVICE ecu)
{
    pugi::xml_document doc;

    // 添加根节点
    pugi::xml_node root = doc.append_child("otx");
    root.append_attribute("xsi:schemaLocation").set_value("http://iso.org/OTX/1.0.0/Auxiliaries/DiagMetaData  ../../../Schema/Auxiliaries/otxDiagMetaData.xsd&#13;&#10; http://iso.org/OTX/1.0.0  ../../../Schema/Core/otx.xsd&#13;&#10; http://iso.org/OTX/1.0.0/DateTime  ../../../Schema/StandardInterface/otxIFD_DateTime.xsd&#13;&#10; http://iso.org/OTX/1.0.0/DiagCom  ../../../Schema/StandardInterface/otxIFD_DiagCom.xsd&#13;&#10; http://iso.org/OTX/1.0.0/DiagDataBrowsing  ../../../Schema/StandardInterface/otxIFD_DiagDataBrowsing.xsd&#13;&#10; http://iso.org/OTX/1.0.0/Event  ../../../Schema/StandardInterface/otxIFD_Event.xsd&#13;&#10; http://www.softing.com/OTX/softingExtensions/ExternCall  ../../../Schema/softing/ExternCall.xsd&#13;&#10; http://www.softing.com/OTX/softingExtensions/File  ../../../Schema/softing/File.xsd&#13;&#10; http://iso.org/OTX/1.0.0/Flash  ../../../Schema/StandardInterface/otxIFD_Flash.xsd&#13;&#10; http://iso.org/OTX/1.0.0/HMI  ../../../Schema/StandardInterface/otxIFD_HMI.xsd&#13;&#10; http://iso.org/OTX/1.0.0/i18n  ../../../Schema/StandardInterface/otxIFD_I18n.xsd&#13;&#10; http://iso.org/OTX/1.0.0/Logging  ../../../Schema/StandardInterface/otxIFD_Logging.xsd&#13;&#10; http://iso.org/OTX/1.0.0/Math  ../../../Schema/StandardInterface/otxIFD_Math.xsd&#13;&#10; http://iso.org/OTX/1.0.0/Quantities  ../../../Schema/StandardInterface/otxIFD_Quantities.xsd&#13;&#10; http://iso.org/OTX/1.0.0/StringUtil  ../../../Schema/StandardInterface/otxIFD_StringUtil.xsd&#13;&#10; http://www.softing.com/OTX/softingExtensions/GenericIO  ../../../Schema/softing/GenericIO.xsd&#13;&#10; http://www.softing.com/OTX/softingExtensions/SoftingDiagnostics  ../../../Schema/softing/SoftingDiagnostics.xsd");
    root.append_attribute("id").set_value("Otx201907051405070546801");
    root.append_attribute("name").set_value("FCS_Initial_Dynamic_Calibration");
    root.append_attribute("package").set_value("package");
    root.append_attribute("version").set_value("");
    root.append_attribute("xmlns").set_value("http://iso.org/OTX/1.0.0");
    root.append_attribute("xmlns:datetime").set_value("http://iso.org/OTX/1.0.0/DateTime");
    root.append_attribute("xmlns:diag").set_value("http://iso.org/OTX/1.0.0/DiagCom");
    root.append_attribute("xmlns:diagbr").set_value("http://iso.org/OTX/1.0.0/DiagDataBrowsing");
    root.append_attribute("xmlns:ev").set_value("http://iso.org/OTX/1.0.0/Event");
    root.append_attribute("xmlns:externcall").set_value("http://www.softing.com/OTX/softingExtensions/ExternCall");
    root.append_attribute("xmlns：file").set_value("http://www.softing.com/OTX/softingExtensions/File");
    root.append_attribute("xmlns:flash").set_value("http://iso.org/OTX/1.0.0/Flash");
    root.append_attribute("xmlns:hmi").set_value("http://iso.org/OTX/1.0.0/HMI");
    root.append_attribute("xmlns:i18n").set_value("http://iso.org/OTX/1.0.0/i18n");
    root.append_attribute("xmlns:log").set_value("http://iso.org/OTX/1.0.0/Logging");
    root.append_attribute("xmlns:math").set_value("http://iso.org/OTX/1.0.0/Math");
    root.append_attribute("xmlns:quant").set_value("http://iso.org/OTX/1.0.0/Quantities");
    root.append_attribute("xmlns:str").set_value("http://iso.org/OTX/1.0.0/StringUtil");
    root.append_attribute("xmlns:genericIO").set_value("http://www.softing.com/OTX/softingExtensions/GenericIO");
    root.append_attribute("xmlns:softingDiagnostics").set_value("http://www.softing.com/OTX/softingExtensions/SoftingDiagnostics");
    root.append_attribute("xmlns:xmime").set_value("http://www.w3.org/2005/05/xmlmime");
    root.append_attribute("xmlns:xsi").set_value("http://www.w3.org/2001/XMLSchema-instance");
    root.append_attribute("xmlns:diagmeta").set_value("http://iso.org/OTX/1.0.0/Auxiliaries/DiagMetaData");

    // 添加子节点
    pugi::xml_node child1 = root.append_child("metaData");
    child1.append_attribute("id").set_value(1);
    child1.append_child(pugi::node_pcdata).set_value("Some data for child 1");

    pugi::xml_node child2 = root.append_child("declarations");
    child2.append_attribute("id").set_value(2);
    child2.append_child(pugi::node_pcdata).set_value("Some data for child 2");

    pugi::xml_node procedures = root.append_child("procedures");
    pugi::xml_node procedureNode = procedures.append_child("procedure");
    procedureNode.append_attribute("id").set_value(QString("Procedure" + getSysTime()).toLatin1().data());
    procedureNode.append_attribute("name").set_value("main");
    procedureNode.append_attribute("visibility").set_value("PUBLIC");
    pugi::xml_node metaData = procedureNode.append_child("metaData");
    pugi::xml_node realisationNode = procedureNode.append_child("realisation");
    pugi::xml_node declarationsNode = realisationNode.append_child("declarations");
    pugi::xml_node flowNode = realisationNode.append_child("flow");
    int chart_count = 0;

    Chart_Base *m_char = charts.at(0);
    PaintChartType type = m_char->getChartType();
    Chart_Line *lineEndPaint;
    while(m_char != nullptr)
    {
        chart_count++;
        type = m_char->getChartType();
        if(m_char->isSave)
             continue;
        if(type == PaintChartType::RECT)
        {
            pugi::xml_node actionNode = flowNode.append_child("action");
            actionNode.append_attribute("id").set_value(QString("Action" + getSysTime()).toLatin1().data());
            pugi::xml_node metaDataNode_1 = actionNode.append_child("metaData");
            pugi::xml_node dataNode_1 = metaDataNode_1.append_child("data");
            dataNode_1.append_attribute("key").set_value("BlockColors");
            pugi::xml_node dataNode_2 = metaDataNode_1.append_child("data");
            dataNode_2.append_attribute("key").set_value("BlockPositions");
            QString pos = QString("%1").arg(m_char->paintStart.x()) + "," + QString("%1").arg(m_char->paintStart.y());
            dataNode_2.append_child(pugi::node_pcdata).set_value(pos.toLatin1().data());
            if(m_char->chartText.textType2->toPlainText().split('-').at(0) == "diag:ExecuteDiagService")
            {
                actionNode = insertDiagnostic(m_char, actionNode,metaDataNode_1,ecu);
            }
            else
            {
                actionNode = insertDiag(m_char,actionNode);
            }

            if(m_char->magPoint.i_point[5]->i_lineStart.size() != 0)
            {
                lineEndPaint = reinterpret_cast<Chart_Line *>(m_char->magPoint.i_point[5]->i_lineStart.at(0));
                m_char = lineEndPaint->getEndChart();
            }
            else {
                break;
            }

        }
        else if(type == PaintChartType::DIAMOND)
        {
            pugi::xml_node branchNode = flowNode.append_child("branch");
            branchNode.append_attribute("id").set_value(QString("branch" + getSysTime()).toLatin1().data());
            pugi::xml_node metaDataNode_1 = branchNode.append_child("metaData");
            pugi::xml_node dataNode_1 = metaDataNode_1.append_child("data");
            dataNode_1.append_attribute("key").set_value("BlockColors");
            pugi::xml_node dataNode_2 = metaDataNode_1.append_child("data");
            dataNode_2.append_attribute("key").set_value("BlockPositions");
            QString pos = QString("%1").arg(m_char->paintStart.x()) + "," + QString("%1").arg(m_char->paintStart.y());
            dataNode_2.append_child(pugi::node_pcdata).set_value(pos.toLatin1().data());
            pugi::xml_node realisationNode_1 = branchNode.append_child("realisation");
            pugi::xml_node ifNode_1 = realisationNode_1.append_child("if");
            pugi::xml_node conditionNode_1 = ifNode_1.append_child("condition");
            conditionNode_1.append_attribute("id").set_value(QString("ConditionHeader" + getSysTime()).toLatin1().data());
            pugi::xml_node realisationNode_2 = conditionNode_1.append_child("realisation");
            realisationNode_2.append_attribute("xsi:type").set_value("IsEqual");
            QString lastChartText = charts[chart_count - 2]->chartText.textType2->toPlainText().split('-').at(0);
            QString termValue = m_char->chartText.textType2->toPlainText().split('-').at(0);
            m_char->isSave = true;
            if(lastChartText == "diag:ExecuteDiagService")
            {
                pugi::xml_node termNode_1 = realisationNode_2.append_child("term");
                termNode_1.append_attribute("valueOf").set_value("resultState");
                termNode_1.append_attribute("xsi:type").set_value("diag:ResultStateValue");
                pugi::xml_node termNode_2 = realisationNode_2.append_child("term");
                termNode_2.append_attribute("value").set_value(termValue.toLatin1().data());
                termNode_2.append_attribute("xsi:type").set_value("diag:ResultStateLiteral");
            }
            else if(lastChartText == "hmi:ConfirmDialog")
            {
                pugi::xml_node termNode_1 = realisationNode_2.append_child("term");
                termNode_1.append_attribute("valueOf").set_value("ChooseStatus");
                termNode_1.append_attribute("xsi:type").set_value("hmi:ConfirmationTypeValue");
                pugi::xml_node termNode_2 = realisationNode_2.append_child("term");
                termNode_2.append_attribute("value").set_value(termValue.toLatin1().data());
                termNode_2.append_attribute("xsi:type").set_value("hmi:ConfirmationTypeLiteral");
            }

            pugi::xml_node flowNode_1 = ifNode_1.append_child("flow");
            pugi::xml_node elseifNode_1 = realisationNode_1.append_child("elseif");
            pugi::xml_node conditionNode_2 = elseifNode_1.append_child("condition");
            conditionNode_2.append_attribute("id").set_value(QString("ConditionHeader" + getSysTime()).toLatin1().data());
            pugi::xml_node realisationNode_3 = conditionNode_2.append_child("realisation");
            realisationNode_3.append_attribute("xsi:type").set_value("IsEqual");
            QString termValue_2 = m_char->chartText.textType2->toPlainText().split('-').at(1);
            if(lastChartText == "diag:ExecuteDiagService")
            {
                pugi::xml_node termNode_1 = realisationNode_3.append_child("term");
                termNode_1.append_attribute("valueOf").set_value("resultState");
                termNode_1.append_attribute("xsi:type").set_value("diag:ResultStateValue");
                pugi::xml_node termNode_2 = realisationNode_3.append_child("term");
                termNode_2.append_attribute("value").set_value(termValue_2.toLatin1().data());
                termNode_2.append_attribute("xsi:type").set_value("diag:ResultStateLiteral");
            }
            else if(lastChartText == "hmi:ConfirmDialog")
            {
                pugi::xml_node termNode_1 = realisationNode_3.append_child("term");
                termNode_1.append_attribute("valueOf").set_value("ChooseStatus");
                termNode_1.append_attribute("xsi:type").set_value("hmi:ConfirmationTypeValue");
                pugi::xml_node termNode_2 = realisationNode_3.append_child("term");
                termNode_2.append_attribute("value").set_value(termValue_2.toLatin1().data());
                termNode_2.append_attribute("xsi:type").set_value("hmi:ConfirmationTypeLiteral");
            }
            pugi::xml_node flowNode_2 = elseifNode_1.append_child("flow");
            //branch node process precudure
            if(m_char->magPoint.i_point[1]->i_lineStart.size() != 0)
            {
               Chart_Line *lineEnd = reinterpret_cast<Chart_Line *>(m_char->magPoint.i_point[1]->i_lineStart.at(0));
               Chart_Base *embedded_chart = lineEnd->getEndChart();
               if(embedded_chart->getChartType() == PaintChartType::DIAMOND)
               {

               }
               else if(embedded_chart->getChartType() == PaintChartType::RECT)
               {
                    while (embedded_chart != nullptr) {
                        pugi::xml_node embedded_actionNode = flowNode_2.append_child("action");
                        embedded_actionNode.append_attribute("id").set_value(QString("Action" + getSysTime()).toLatin1().data());
                        pugi::xml_node embedded_metaDataNode = embedded_actionNode.append_child("metaData");
                        pugi::xml_node dataNode_embedded = embedded_metaDataNode.append_child("data");
                        dataNode_embedded.append_attribute("key").set_value("BlockColors");
                        pugi::xml_node dataNode_2_embedded = embedded_metaDataNode.append_child("data");
                        dataNode_2_embedded.append_attribute("key").set_value("BlockPositions");
                        QString pos = QString("%1").arg(embedded_chart->paintStart.x()) + "," + QString("%1").arg(embedded_chart->paintStart.y());
                        dataNode_2_embedded.append_child(pugi::node_pcdata).set_value(pos.toLatin1().data());
                        if(embedded_chart->chartText.textType2->toPlainText().split('-').at(0) == "diag:ExecuteDiagService")
                        {
                            embedded_actionNode = insertDiagnostic(embedded_chart, embedded_actionNode,embedded_metaDataNode,ecu);
                        }
                        else
                        {
                            embedded_actionNode = insertDiag(embedded_chart,embedded_actionNode);
                        }
                        if(embedded_chart->magPoint.i_point[5]->i_lineStart.size() != 0)
                        {
                            lineEnd = reinterpret_cast<Chart_Line *>(embedded_chart->magPoint.i_point[5]->i_lineStart.at(0));
                            embedded_chart = lineEnd->getEndChart();
                        }
                        else {
                            break;
                        }
                    }
               }
            }
            if(m_char->magPoint.i_point[2]->i_lineStart.size() != 0)
            {
                lineEndPaint = reinterpret_cast<Chart_Line *>(m_char->magPoint.i_point[2]->i_lineStart.at(0));
                m_char = lineEndPaint->getEndChart();
            }
            else {
                break;
            }
        }

    }











//    foreach (Chart_Base *m_char, charts) {
//        chart_count++;
//        PaintChartType type = m_char->getChartType();
//        if(m_char->isSave)
//            continue;
//        if(type == PaintChartType::RECT)
//        {
//            pugi::xml_node actionNode = flowNode.append_child("action");
//            actionNode.append_attribute("id").set_value(QString("Action" + getSysTime()).toLatin1().data());
//            pugi::xml_node metaDataNode_1 = actionNode.append_child("metaData");
//            pugi::xml_node dataNode_1 = metaDataNode_1.append_child("data");
//            dataNode_1.append_attribute("key").set_value("BlockColors");
//            pugi::xml_node dataNode_2 = metaDataNode_1.append_child("data");
//            dataNode_2.append_attribute("key").set_value("BlockPositions");
//            QString pos = QString("%1").arg(m_char->paintStart.x()) + "," + QString("%1").arg(m_char->paintStart.y());
//            dataNode_2.append_child(pugi::node_pcdata).set_value(pos.toLatin1().data());
//            if(m_char->chartText.textType2->toPlainText().split('-').at(0) == "diag:ExecuteDiagService")
//            {

//                actionNode = insertDiagnostic(m_char, actionNode,metaDataNode_1,ecu);
//            }
//            else
//            {
//                actionNode = insertDiag(m_char,actionNode);
//            }
//        }
//        else if(type == PaintChartType::DIAMOND)
//        {
//            pugi::xml_node branchNode = flowNode.append_child("branch");
//            branchNode.append_attribute("id").set_value(QString("branch" + getSysTime()).toLatin1().data());
//            pugi::xml_node metaDataNode_1 = branchNode.append_child("metaData");
//            pugi::xml_node dataNode_1 = metaDataNode_1.append_child("data");
//            dataNode_1.append_attribute("key").set_value("BlockColors");
//            pugi::xml_node dataNode_2 = metaDataNode_1.append_child("data");
//            dataNode_2.append_attribute("key").set_value("BlockPositions");
//            QString pos = QString("%1").arg(m_char->paintStart.x()) + "," + QString("%1").arg(m_char->paintStart.y());
//            dataNode_2.append_child(pugi::node_pcdata).set_value(pos.toLatin1().data());
//            pugi::xml_node realisationNode_1 = branchNode.append_child("realisation");
//            pugi::xml_node ifNode_1 = realisationNode_1.append_child("if");
//            pugi::xml_node conditionNode_1 = ifNode_1.append_child("condition");
//            conditionNode_1.append_attribute("id").set_value(QString("ConditionHeader" + getSysTime()).toLatin1().data());
//            pugi::xml_node realisationNode_2 = conditionNode_1.append_child("realisation");
//            realisationNode_2.append_attribute("xsi:type").set_value("IsEqual");
//            QString lastChartText = charts[chart_count - 2]->chartText.textType2->toPlainText().split('-').at(0);
//            QString termValue = m_char->chartText.textType2->toPlainText().split('-').at(0);
//            m_char->isSave = true;
//            if(lastChartText == "diag:ExecuteDiagService")
//            {
//                pugi::xml_node termNode_1 = realisationNode_2.append_child("term");
//                termNode_1.append_attribute("valueOf").set_value("resultState");
//                termNode_1.append_attribute("xsi:type").set_value("diag:ResultStateValue");
//                pugi::xml_node termNode_2 = realisationNode_2.append_child("term");
//                termNode_2.append_attribute("value").set_value(termValue.toLatin1().data());
//                termNode_2.append_attribute("xsi:type").set_value("diag:ResultStateLiteral");
//            }
//            else if(lastChartText == "hmi:ConfirmDialog")
//            {
//                pugi::xml_node termNode_1 = realisationNode_2.append_child("term");
//                termNode_1.append_attribute("valueOf").set_value("ChooseStatus");
//                termNode_1.append_attribute("xsi:type").set_value("hmi:ConfirmationTypeValue");
//                pugi::xml_node termNode_2 = realisationNode_2.append_child("term");
//                termNode_2.append_attribute("value").set_value(termValue.toLatin1().data());
//                termNode_2.append_attribute("xsi:type").set_value("hmi:ConfirmationTypeLiteral");
//            }

//            pugi::xml_node flowNode_1 = ifNode_1.append_child("flow");
//            pugi::xml_node elseifNode_1 = realisationNode_1.append_child("elseif");
//            pugi::xml_node conditionNode_2 = elseifNode_1.append_child("condition");
//            conditionNode_2.append_attribute("id").set_value(QString("ConditionHeader" + getSysTime()).toLatin1().data());
//            pugi::xml_node realisationNode_3 = conditionNode_2.append_child("realisation");
//            realisationNode_3.append_attribute("xsi:type").set_value("IsEqual");
//            QString termValue_2 = m_char->chartText.textType2->toPlainText().split('-').at(1);
//            if(lastChartText == "diag:ExecuteDiagService")
//            {
//                pugi::xml_node termNode_1 = realisationNode_3.append_child("term");
//                termNode_1.append_attribute("valueOf").set_value("resultState");
//                termNode_1.append_attribute("xsi:type").set_value("diag:ResultStateValue");
//                pugi::xml_node termNode_2 = realisationNode_3.append_child("term");
//                termNode_2.append_attribute("value").set_value(termValue_2.toLatin1().data());
//                termNode_2.append_attribute("xsi:type").set_value("diag:ResultStateLiteral");
//            }
//            else if(lastChartText == "hmi:ConfirmDialog")
//            {
//                pugi::xml_node termNode_1 = realisationNode_3.append_child("term");
//                termNode_1.append_attribute("valueOf").set_value("ChooseStatus");
//                termNode_1.append_attribute("xsi:type").set_value("hmi:ConfirmationTypeValue");
//                pugi::xml_node termNode_2 = realisationNode_3.append_child("term");
//                termNode_2.append_attribute("value").set_value(termValue_2.toLatin1().data());
//                termNode_2.append_attribute("xsi:type").set_value("hmi:ConfirmationTypeLiteral");
//            }
//            pugi::xml_node flowNode_2 = elseifNode_1.append_child("flow");
//            //branch node process precudure
//            if(m_char->magPoint.i_point[1]->i_lineStart.size() != 0)
//            {
//               Chart_Line *lineEnd = reinterpret_cast<Chart_Line *>(m_char->magPoint.i_point[1]->i_lineStart.at(0));
//               Chart_Base *embedded_chart = lineEnd->getEndChart();
//               if(embedded_chart->getChartType() == PaintChartType::DIAMOND)
//               {

//               }
//               else if(embedded_chart->getChartType() == PaintChartType::RECT)
//               {
//                    while (embedded_chart != nullptr) {
//                        pugi::xml_node embedded_actionNode = flowNode_2.append_child("action");
//                        embedded_actionNode.append_attribute("id").set_value(QString("Action" + getSysTime()).toLatin1().data());
//                        pugi::xml_node embedded_metaDataNode = embedded_actionNode.append_child("metaData");
//                        pugi::xml_node dataNode_embedded = embedded_metaDataNode.append_child("data");
//                        dataNode_embedded.append_attribute("key").set_value("BlockColors");
//                        pugi::xml_node dataNode_2_embedded = embedded_metaDataNode.append_child("data");
//                        dataNode_2_embedded.append_attribute("key").set_value("BlockPositions");
//                        QString pos = QString("%1").arg(embedded_chart->paintStart.x()) + "," + QString("%1").arg(embedded_chart->paintStart.y());
//                        dataNode_2_embedded.append_child(pugi::node_pcdata).set_value(pos.toLatin1().data());
//                        if(embedded_chart->chartText.textType2->toPlainText().split('-').at(0) == "diag:ExecuteDiagService")
//                        {
//                            embedded_actionNode = insertDiagnostic(embedded_chart, embedded_actionNode,embedded_metaDataNode,ecu);
//                        }
//                        else
//                        {
//                            embedded_actionNode = insertDiag(embedded_chart,embedded_actionNode);
//                        }
//                        if(embedded_chart->magPoint.i_point[5]->i_lineStart.size() != 0)
//                        {
//                            lineEnd = reinterpret_cast<Chart_Line *>(embedded_chart->magPoint.i_point[5]->i_lineStart.at(0));
//                            embedded_chart = lineEnd->getEndChart();
//                        }
//                        else {
//                            break;
//                        }
//                    }
//               }
//            }
//        }
//    }

    procedures.append_child(pugi::node_pcdata).set_value("Some data for child 2");

    // 保存 XML 文件
    if (doc.save_file("output.otx")) {
        std::cout << "XML file saved successfully." << std::endl;
    } else {
        std::cout << "Error saving XML file." << std::endl;
    }
}

pugi::xml_node FlowChart::insertDiag(Chart_Base *m_char, pugi::xml_node actionNode)
{
    m_char->isSave = true;
    if(m_char->chartText.textType2->toPlainText().split('-').at(0) == "hmi:ConfirmDialog")
    {
        pugi::xml_node realisationNode_1 = actionNode.append_child("realisation");
        realisationNode_1.append_attribute("xsi:type").set_value("hmi:ConfirmDialog");
        QString hmiTitle = m_char->chartText.textType2->toPlainText().split('-').at(1);
        QString hmiContent = m_char->chartText.textType2->toPlainText().split('-').at(2);
        QString type = m_char->chartText.textType2->toPlainText().split('-').at(3);
        pugi::xml_node hmiTitleNode = realisationNode_1.append_child("hmi:title");
        hmiTitleNode.append_attribute("value").set_value(hmiTitle.toLatin1().data());
        hmiTitleNode.append_attribute("xsi:type").set_value("StringLiteral");
        pugi::xml_node hmiMessageNode = realisationNode_1.append_child("hmi:message");
        hmiMessageNode.append_attribute("xsi:type").set_value("str:StringConcatenate");
        pugi::xml_node messageNode = hmiMessageNode.append_child("str:string");
        messageNode.append_attribute("value").set_value(hmiContent.toLatin1().data());
        messageNode.append_attribute("xsi:type").set_value("ns:StringLiteral");
        messageNode.append_attribute("xmlns:ns").set_value("http://iso.org/OTX/1.0.0");
        pugi::xml_node hmiMessagetypeNode = realisationNode_1.append_child("hmi:messageType");
        hmiMessagetypeNode.append_attribute("value").set_value(type.toLatin1().data());
        if(type != "INFO" && type!= "WARNING" && type!= "ERROR")
        {
            pugi::xml_node hmiMessageresultNode = realisationNode_1.append_child("hmi:result");
            hmiMessageresultNode.append_attribute("name").set_value("chooseSatus");
        }
    }
    else if(m_char->chartText.textType2->toPlainText().split('-').at(0) == "ns:Assignment")
    {
        pugi::xml_node realisationNode_1 = actionNode.append_child("realisation");
        realisationNode_1.append_attribute("xsi:type").set_value("ns:Assignment");
        realisationNode_1.append_attribute("xmlns:ns").set_value("http://iso.org/OTX/1.0.0");
        QString name = m_char->chartText.textType2->toPlainText().split('-').at(1);
        QString value = m_char->chartText.textType2->toPlainText().split('-').at(2);
        pugi::xml_node result = realisationNode_1.append_child("result");
        result.append_attribute("name").set_value(name.toLatin1().data());
        if(name.contains("List"))
        {
           result.append_attribute("xsi:type").set_value("ns:ListVariable");
        }
        else
        {
            result.append_attribute("xsi:type").set_value("ns:StringValue");
        }

        pugi::xml_node term = realisationNode_1.append_child("term");
        term.append_attribute("valueOf").set_value(value.toLatin1().data());
    }
    else if(m_char->chartText.textType2->toPlainText().split('-').at(0) == "hmi:ChoiceDialog")
    {
         pugi::xml_node realisationNode_1 = actionNode.append_child("realisation");
         realisationNode_1.append_attribute("xsi:type").set_value("hmi:ChoiceDialog");
         QString title = m_char->chartText.textType2->toPlainText().split('-').at(1);
         QString information = m_char->chartText.textType2->toPlainText().split('-').at(2);
         QString category =  m_char->chartText.textType2->toPlainText().split('-').at(3);
         QString resultName = m_char->chartText.textType2->toPlainText().split('-').at(4);
         pugi::xml_node titleNode = realisationNode_1.append_child("hmi:title");
         titleNode.append_attribute("value").set_value(title.toLatin1().data());
         titleNode.append_attribute("xsi:type").set_value("StringLitera");
         pugi::xml_node messageNode = realisationNode_1.append_child("hmi:message");
         messageNode.append_attribute("value").set_value(information.toLatin1().data());
         messageNode.append_attribute("xsi:type").set_value("StringLitera");
         pugi::xml_node optionNode = realisationNode_1.append_child("hmi:options");
         optionNode.append_attribute("valueOf").set_value(category.toLatin1().data());
         optionNode.append_attribute("xsi:type").set_value("ListValue");
         pugi::xml_node defaultNode = realisationNode_1.append_child("hmi:default");
         defaultNode.append_attribute("value").set_value("-1");
         defaultNode.append_attribute("xsi:type").set_value("IntegerLiteral");
         pugi::xml_node resultNode = realisationNode_1.append_child("hmi:result");
         resultNode.append_attribute("name").set_value(resultName.toLatin1().data());
     }
    else if(m_char->chartText.textType2->toPlainText().split('-').at(0) == "hmi:InputDialog")
    {
        pugi::xml_node realisationNode_1 = actionNode.append_child("realisation");
        realisationNode_1.append_attribute("xsi:type").set_value("hmi:InputDialog");
        QString title = m_char->chartText.textType2->toPlainText().split('-').at(1);
        QString message = m_char->chartText.textType2->toPlainText().split('-').at(2);
        QString instruction =  m_char->chartText.textType2->toPlainText().split('-').at(3);
        QString resultName = m_char->chartText.textType2->toPlainText().split('-').at(4);
        pugi::xml_node titleNode = realisationNode_1.append_child("hmi:title");
        titleNode.append_attribute("value").set_value(title.toLatin1().data());
        titleNode.append_attribute("xsi:type").set_value("StringLitera");
        pugi::xml_node messageNode = realisationNode_1.append_child("hmi:message");
        messageNode.append_attribute("value").set_value(message.toLatin1().data());
        messageNode.append_attribute("xsi:type").set_value("StringLitera");
        pugi::xml_node optionNode = realisationNode_1.append_child("hmi:initialValue");
        optionNode.append_attribute("valueOf").set_value(resultName.toLatin1().data());
        optionNode.append_attribute("xsi:type").set_value("StringValue");
        pugi::xml_node defaultNode = realisationNode_1.append_child("hmi:instruction");
        defaultNode.append_attribute("value").set_value(instruction.toLatin1().data());
        defaultNode.append_attribute("xsi:type").set_value("StringLiteral");
        pugi::xml_node resultNode = realisationNode_1.append_child("hmi:result");
        resultNode.append_attribute("name").set_value(resultName.toLatin1().data());
    }
    else if(m_char->chartText.textType2->toPlainText().split('-').at(0) == "event:WaitForEvent")
    {
        pugi::xml_node realisationNode_1 = actionNode.append_child("realisation");
        realisationNode_1.append_attribute("xsi:type").set_value("event:WaitForEvent");
//        pugi::xml_node eventNode_1 = realisationNode_1.append_child("event:source");
//        eventNode_1.append_attribute("xsi:type").set_value("event:EventSourceValue");
//        eventNode_1.append_attribute("valueOf").set_value("xMonitor");
        pugi::xml_node eventNode_2 = realisationNode_1.append_child("event:source");
        eventNode_2.append_attribute("xsi:type").set_value("event:TimerExpiredEventSource");
        pugi::xml_node timeoutNode_2 = eventNode_2.append_child("event:timeout");
        QString timeout = m_char->chartText.textType2->toPlainText().split('-').at(1);
        timeoutNode_2.append_attribute("value").set_value(timeout.toLatin1().data());
        timeoutNode_2.append_attribute("xsi:type").set_value("IntegerLiteral");
        pugi::xml_node eventNode_3 = realisationNode_1.append_child("event:event");
        eventNode_3.append_attribute("name").set_value("timeoutEvent");
    }
    return actionNode;
}

pugi::xml_node FlowChart::insertDiagnostic(Chart_Base *m_char, pugi::xml_node actionNode,pugi::xml_node metaDataNode_1,ECU_SERVICE ecu)
{
    pugi::xml_node dataNode_3 = metaDataNode_1.append_child("data");
    dataNode_3.append_attribute("key").set_value("AssumedLinkAndService");
    pugi::xml_node dataNode_4 = dataNode_3.append_child("diagmeta:DiagMetaData");
    pugi::xml_node dataNode_5 = dataNode_4.append_child("diagmeta:comChannelName");

    m_char->isSave = true;
    QString service = m_char->chartText.textType2->toPlainText().split('-').at(1);
    foreach (Service ecuservice, ecu.Services) {//serviceName在odx-v中有requestParam，则这里有diag:requestParameters节点
        if(ecuservice.serviceName == service)
        {
            dataNode_5.append_attribute("value").set_value(ecuservice.ECUID.toLatin1().data());  //odx-v文件中的ECU的名字
            pugi::xml_node dataNode_6 = dataNode_4.append_child("diagmeta:diagServiceName");
            QString name = ecuservice.ServiceClass.split(".").at(ecuservice.ServiceClass.split(".").size() - 1);
            dataNode_6.append_attribute("value").set_value(name.toLatin1().data());
            pugi::xml_node realisationNode_1 = actionNode.append_child("realisation");

            realisationNode_1.append_attribute("xsi:type").set_value("diag:ExecuteDiagService");
            pugi::xml_node diagNode_1 = realisationNode_1.append_child("diag:diagService");
            diagNode_1.append_attribute("xsi:type").set_value("diag:CreateDiagServiceByName");
            pugi::xml_node diagchannel = diagNode_1.append_child("diag:comChannel");
            diagchannel.append_attribute("valueOf").set_value("comChannel");
            diagchannel.append_attribute("xsi:type").set_value("diag:ComChannelValue");
            pugi::xml_node diagName = diagNode_1.append_child("diag:name");


            if(ecuservice.serviceparams.child_params.child_param.size() != 0)
            {
                diagName.append_attribute("value").set_value(name.toLatin1().data());
                diagName.append_attribute("xsi:type").set_value("ns:StringLiteral");
                diagName.append_attribute("xmlns:ns").set_value("http://iso.org/OTX/1.0.0");
                pugi::xml_node requestParameters = realisationNode_1.append_child("diag:requestParameters");
                pugi::xml_node requestParameter_1 = requestParameters.append_child("diag:requestParameter");
                pugi::xml_node diagvalue = requestParameter_1.append_child("diag:value");
                diagvalue.append_attribute("value").set_value(service.toLatin1().data());
                diagvalue.append_attribute("xsi:type").set_value("StringLiteral");
                pugi::xml_node diagpath = requestParameter_1.append_child("diag:path");
                foreach (DOPPARAM param, ecuservice.serviceparams.child_params.child_param) {
                    pugi::xml_node stepName = diagpath.append_child("stepByName");
                    stepName.append_attribute("value").set_value(param.child_short_name.toLatin1().data());
                    stepName.append_attribute("xsi:type").set_value("ns:StringLiteral");
                    stepName.append_attribute("xmlns:ns").set_value("http://iso.org/OTX/1.0.0");
                }
                pugi::xml_node responseParameters = realisationNode_1.append_child("diag:responseParameters");
                pugi::xml_node responseName = responseParameters.append_child("diag:name");
                responseName.append_attribute("value").set_value("dummy");
                responseName.append_attribute("xsi:type").set_value("StringLiteral");
                pugi::xml_node responseParameter_1 = responseParameters.append_child("diag:responseParam");
                pugi::xml_node targetName = responseParameter_1.append_child("diag:target");
                targetName.append_attribute("name").set_value("DIDA3F4_Status_State"); //读取odx-v文件中POS
                targetName.append_attribute("xsi:type").set_value("StringVariable");

                pugi::xml_node targetpath = responseParameter_1.append_child("diag:path");

            }
            else
            {
                diagName.append_attribute("value").set_value(service.toLatin1().data());
                diagName.append_attribute("xsi:type").set_value("ns:StringLiteral");
                diagName.append_attribute("xmlns:ns").set_value("http://iso.org/OTX/1.0.0");
            }
            pugi::xml_node diagresult = realisationNode_1.append_child("diag:result");
            diagresult.append_attribute("name").set_value("Result");
            pugi::xml_node diagresultState = realisationNode_1.append_child("diag:resultState");
            diagresultState.append_attribute("name").set_value("resultState");
            break;
        }
    }
}

QString FlowChart::getSysTime()
{
    auto now = std::chrono::system_clock::now();

    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long msecond = tv.tv_usec;

    struct std::tm bt;
    localtime_r(&now_time, &bt);


    int year = bt.tm_year + 1900;
    int month = bt.tm_mon + 1;
    int day = bt.tm_mday;
    int hour = bt.tm_hour;
    int min = bt.tm_min;
    int second = bt.tm_sec;

    QString time = QString("%1%2%3%4%5%6%7").arg(year,4,10,QLatin1Char('0')).arg(month,2,10,QLatin1Char('0')).arg(day,2,10,QLatin1Char('0'))
            .arg(hour,2,10,QLatin1Char('0')).arg(min,2,10,QLatin1Char('0')).arg(second,2,10,QLatin1Char('0')).arg(msecond,7,10,QLatin1Char('0'));

    return time;
}

bool FlowChart::newChartFile()
{
    if(!fileIsSaved)
    {
        QMessageBox tmp(QMessageBox::Warning,tr("警告！"),tr("不保存文件就关闭？"),QMessageBox::NoButton,this->parentWidget());
        QPushButton *saveclose = tmp.addButton(tr("保存并关闭"),QMessageBox::ActionRole);
        QPushButton *nosaveclose = tmp.addButton(tr("不保存关闭"),QMessageBox::AcceptRole);
        QPushButton *cancel = tmp.addButton(tr("取消"),QMessageBox::RejectRole);
        tmp.exec();
        if(tmp.clickedButton() == saveclose)
        {
            ECU_SERVICE ecu;
            if(saveChartFile(ecu))
            {
                resetFlowChartPanel();
            }else{
                return false;
            }
            //qDebug()<<"Save and Quit";

        }else if(tmp.clickedButton() == nosaveclose)
        {
            //qDebug()<<"Not Save and Quit";
            resetFlowChartPanel();
        }else if(tmp.clickedButton() == cancel)
        {
            //qDebug()<<"cancel ";
        }
    }else{
        resetFlowChartPanel();
    }
    return true;
}

//void FlowChart::resetSeletcChart()
//{
//    if(curSelecChart != nullptr) curSelecChart->hideMagSize();
//    curSelecChart = nullptr;
//}

Chart_Base * FlowChart::getCurSeleChart()
{
    return curSelecChart;
}


void FlowChart::addChart(Chart_Base *cb)
{
    charts.push_back(cb);
}

bool FlowChart::delChart(Chart_Base *&cb)
{
    for(auto it = charts.begin();it != charts.end();it++)
    {
        if(*it == cb)
        {
            Chart_Base *tmp = cb;
            cb = nullptr;
            charts.erase(it);
#if 1
            for(auto magit = tmp->magPoint.i_point.begin();magit!=tmp->magPoint.i_point.end();magit++)
            {
                for(auto magLineStIt = (*magit)->i_lineStart.begin();magLineStIt != (*magit)->i_lineStart.end();magLineStIt++)
                {
                    dynamic_cast<Chart_Line*>(*magLineStIt) ->resetEndChart();
                    if(!delLine(*magLineStIt))
                    {
                        qDebug()<<"Error";
                    }else{
                        qDebug()<<"Succeed.";
                    }
                }
                for(auto magLineEnIt = (*magit)->i_lineEnd.begin();magLineEnIt != (*magit)->i_lineEnd.end();magLineEnIt++)
                {
                    dynamic_cast<Chart_Line*>(*magLineEnIt) ->resetStartChart();
                    if(!delLine(*magLineEnIt))
                    {
                        qDebug()<<"Error";
                    }else{
                        qDebug()<<"Succeed.";
                    }
                }
            }
#endif
            delete tmp;

            return true;
        }
    }
    return false;
}

void FlowChart::addLine(Chart_Base *cb)
{
    line.push_back(cb);
}

bool FlowChart::delLine(Chart_Base *&cb)
{
    for(auto it = line.begin();it != line.end();it++)
    {
        if(*it == cb)
        {
            Chart_Line *tmp = dynamic_cast<Chart_Line*>(*it);
            cb = nullptr;
            line.erase(it);
            qDebug()<<tmp->magPoint.i_point.size();


            tmp->resetEndChart();
            tmp->resetStartChart();
            delete tmp;
            return true;
        }
    }
    return false;
}

void FlowChart::hideMagSizeAll()
{
    for(auto it = charts.begin();it!=charts.end();it++)
    {
        (*it)->hideMagSize();
    }
    for(auto it = line.begin();it!=line.end();it++)
    {
        (*it)->hideMagSize();
    }
    curSelecChart = nullptr;
    mouseEventType = MOUSE_EVENT_TYPE::NONE;
    emit disableStyle();
}

bool FlowChart::saveFile(QString filePath)
{
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    QDataStream fout(&file);

    Chart_Base::saveStaticValue(fout);
    unsigned long long i;
    i = charts.size();
    fout.writeRawData(reinterpret_cast<const char*>(&i),sizeof(unsigned long long));
    for(auto it = charts.begin(); it!=charts.end(); it++)
    {
        fout<<*(*it);
    }
    i = line.size();
    fout.writeRawData(reinterpret_cast<const char*>(&i),sizeof(unsigned long long));
    for(auto it = line.begin(); it!=line.end(); it++)
    {
        fout<<*(*it)<<*(reinterpret_cast<const Chart_Line*>(*it));
    }
    file.close();
    return true;
}

bool FlowChart::loadFile(QString filePath)
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QDataStream fin(&file);
    std::map<int,Chart_Base*> chartMap;

    Chart_Base::loadStaticValue(fin);
    unsigned long long cnt;
    fin.readRawData(reinterpret_cast<char*>(&cnt),sizeof(unsigned long long));
    qDebug()<<"图形个数："<<cnt;
    for(unsigned long long i = 0;i<cnt;i++)
    {
        PaintChartType tmp;
        Chart_Base *cb;
        fin.readRawData(reinterpret_cast<char*>(&tmp),sizeof(PaintChartType));
        switch(tmp)
        {

            case PaintChartType::RECT:
            {
                cb = new Chart_Rect(this);
            }break;
            case PaintChartType::DIAMOND:
            {
                cb = new Chart_Diamond(this);
            }break;
            case PaintChartType::ROUNDRECT:
            {
                cb = new Chart_RoundRect(this);
            }break;
            case PaintChartType::ELLIPSE:
            {
                cb = new Chart_Ellipse(this);
            }break;
            case PaintChartType::TRAPEZOID:
            {
                cb = new Chart_Trapezoid(this);
            }break;
            default:case PaintChartType::NONE:{
                cb = nullptr;
            }break;
        }
        cb->chartType = tmp;
        fin>>(*cb);
        connect(cb,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
        connect(cb,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
        connect(cb,SIGNAL(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)),this,SLOT(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)));
        addChart(cb);
        cb->applyWidthHeight();
        cb->update();
        cb->show();
        chartMap[cb->getID()] = cb;
    }
    fin.readRawData(reinterpret_cast<char*>(&cnt),sizeof(unsigned long long));
    qDebug()<<"连线个数："<<cnt;
    for(unsigned long long i = 0;i<cnt;i++)
    {
        PaintChartType tmp;
        Chart_Base *cb;
        Chart_Line *cl;
        int id;
        fin.readRawData(reinterpret_cast<char*>(&tmp),sizeof(PaintChartType));
        cb = new Chart_Line(this);
        addLine(cb);
        if(nullptr == (cl = dynamic_cast<Chart_Line*>(cb))) qDebug()<<"error";
        fin>>(*cb)>>(*cl);
        try{
            fin.readRawData(reinterpret_cast<char*>(&id),sizeof(int));
            if(id>=0)
            {
                Chart_Base *cbs = chartMap.at(id);
                cbs->addMagiPointStartLine(cl->getStartMagIndex(),cl);
                cl->setStartChart(cbs);
            }
        }catch(std::out_of_range &oor){
            qDebug()<<oor.what()<<"Not Found Start chart.";
        }
        try{
            fin.readRawData(reinterpret_cast<char*>(&id),sizeof(int));
            if(id>=0)
            {
                Chart_Base *cbe = chartMap.at(id);
                cbe->addMagiPointEndLine(cl->getEndMagIndex(),cl);
                cl->setEndChart(cbe);
            }
        }catch(std::out_of_range &oor){
            qDebug()<<oor.what()<<"Not Found End chart.";
        }
        connect(cl,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
        connect(cl,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
        cl->applyWidthHeight();
        cl->update();
        cl->show();
    }
    hideMagSizeAll();
    return true;
}

void FlowChart::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(QColor(150,150,150));
    const int gap = 30;
    for(int i = 1;i * gap < width();i++)
    {
        if(i%5 == 0)
            p.drawLine(QLineF(i*gap,0,i*gap,height()));
    }
    for(int i = 1;i * gap < height();i++)
    {
        if(i%5 == 0)
            p.drawLine(QLineF(0,i*gap,width(),i*gap));
    }

    p.setPen(QColor(200,200,200,150));
    //p.setPen(Qt::DotLine);
    //p.setOpacity(200);
    for(int i = 1;i * gap < width();i++)
    {
        if(i%5 == 0) continue;
        p.drawLine(QLineF(i*gap,0,i*gap,height()));
    }
    for(int i = 1;i * gap < height();i++)
    {
        if(i%5 == 0) continue;
        p.drawLine(QLineF(0,i*gap,width(),i*gap));
    }


    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);

    //event->accept();
}

void FlowChart::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
    switch(mouseEventType)
    {
        case MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE:{
            int x = event->pos().rx();
            int y = event->pos().ry();
            //curPaintChart->setObjectName(QStringLiteral("tttt"));
            if(curSelecChart) curSelecChart->hideMagSize();
            curSelecChart = curPaintChart;
            curPaintChart->setXY(x,y);
            //curPaintChart->setAttribute(Qt::WA_StyledBackground,true);
            //curPaintChart->setStyleSheet(QStringLiteral("background-color: rgb(100, 100, 100);"));
            if(curPaintChart->chartType == PaintChartType::LINE)
            {
                connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
                connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
                addLine(curPaintChart);
                Chart_Line *cl = dynamic_cast<Chart_Line*>(curSelecChart);
                emit sendLineStyle(cl->paintChartDrawPen,cl->getStartLineHeadType(),cl->getEndLineHeadType());
            }else
            {
                connect(curPaintChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
                connect(curPaintChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
                connect(curPaintChart,SIGNAL(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)),this,SLOT(setTypeCreateMagPoint(Chart_Base *,ORIENTION,int)));
                //connect(curPaintChart,SIGNAL(hideThisClass()),this,SLOT(resetSeletcChart()));
                addChart(curPaintChart);
                emit sendChartStyle(curSelecChart->paintChartDrawPen,curSelecChart->paintChartFillPen);
            }
            curPaintChart->update();
            curPaintChart->show();
            //mouseEventType = MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE;
            event->accept();
        }break;
        default:case MOUSE_EVENT_TYPE::NONE:{
            for(auto it = charts.begin();it!=charts.end();it++)
            {
                (*it)->overlapChartMousePressed(event);
                if(event->isAccepted()) return;
            }
            for(auto a:line)
            {
                a->overlapChartMousePressed(event);
                if(event->isAccepted()) return;
            }
            hideMagSizeAll();
        }break;
    }
}

void FlowChart::mouseMoveEvent(QMouseEvent *event)
{
    //if(event->isAccepted()) return;
    event->ignore();
    switch(mouseEventType)
    {
        default:case MOUSE_EVENT_TYPE::NONE:
        {
            for(auto it = charts.begin();it!=charts.end();it++)
            {
                (*it)->overlapChartMouseMove(event);
                if(event->isAccepted()) return;
            }
            for(auto it = line.begin();it!=line.end();it++)
            {
                (*it)->overlapChartMouseMove(event);
                if(event->isAccepted()) return;
            }
            if(curSelecChart == nullptr)
            {
                setCursor(QCursor(Qt::ArrowCursor));
                hideMagSizeAll();
            }
        }break;
        case MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE:
        {
            int x = event->pos().rx(),y = event->pos().ry();
            if(curSelecChart)
            {
                if(curSelecChart->chartType == PaintChartType::LINE)
                {
                    for(auto it = charts.begin();it!=charts.end();it++)
                    {
                        if((*it)->autoSetMagi(x,y,magPointIndex))
                        {
                            lineSelectChart = *it;
                            break;
                        }else{
                            lineSelectChart = nullptr;
                        }
                    }
                    //if(!lineSelectChart) reinterpret_cast<Chart_Line *>(curSelecChart)->resetEndChart();
                }
                curPaintChart->setWidthHeight(x,y);
            }
            event->accept();
        }break;
        case MOUSE_EVENT_TYPE::RUNTIME_CHANGE_SIZE:
        {
            int x = event->pos().rx(),y = event->pos().ry();

            if(curSelecChart->chartType == PaintChartType::LINE)
            {
                qDebug()<<"hehe";
                for(auto it = charts.begin();it!=charts.end();it++)
                {
                    if((*it)->autoSetMagi(x,y,magPointIndex))
                    {
                        lineSelectChart = *it;
                        break;
                    }else{
                        lineSelectChart = nullptr;
                    }
                }
                //if(!lineSelectChart) reinterpret_cast<Chart_Line *>(curSelecChart)->resetEndChart();
            }
            curSelecChart->setWidthHeight(x,y,sizePointDirect);
            event->accept();
        }break;
        case MOUSE_EVENT_TYPE::RUNTIME_CREATE_MAGPOINT:
        {
            if(newLineChart == nullptr)
            {
                newLineChart = new Chart_Line(this);
                if(curSelecChart)
                    curSelecChart->hideMagSize();
                curSelecChart = newLineChart;
                addLine(newLineChart);
                //newLineChart->setAttribute(Qt::WA_StyledBackground,true);
                //newLineChart->setStyleSheet(QStringLiteral("background-color: rgb(100, 100, 100);"));
                connect(newLineChart,SIGNAL(sendThisClass(Chart_Base *, int,int)),this,SLOT(setSelecChart(Chart_Base *, int,int)));
                connect(newLineChart,SIGNAL(setTypeChangeSize(ORIENTION)),this,SLOT(setTypeChangeSize(ORIENTION)));
                newLineChart->setXY(newLineFromSelectChart->getMagiPointAbsX(magPointFromIndex),newLineFromSelectChart->getMagiPointAbsY(magPointFromIndex));
                newLineChart->setStartChart(newLineFromSelectChart);
                newLineChart->setStartMagIndex(magPointFromIndex);
                newLineChart->setStartDirect(magPointDirect);
                newLineChart->update();
                newLineChart->show();

                newLineFromSelectChart->addMagiPointStartLine(magPointFromIndex,newLineChart);
            }
            int x = event->pos().rx(),y = event->pos().ry();

            for(auto it = charts.begin();it!=charts.end();it++)
            {
                //if(*it == newLineFromSelectChart) continue;
                if((*it)->autoSetMagi(x,y,magPointToIndex))
                {
                    newLineToSelectChart = *it;
                    break;
                }else{
                    newLineToSelectChart = nullptr;
                }
            }
            //if(!newLineToSelectChart) newLineChart->resetEndChart();
            newLineChart->setWidthHeight(x,y,ORIENTION::ENDPOINT);
            event->ignore();
        }break;
        case MOUSE_EVENT_TYPE::RUNTIME_CHANGE_POS:
        {
            if(curSelecChart->chartType != PaintChartType::LINE)
            {
                curSelecChart->setXY(event->pos().rx() - curSelecChartPos.rx(),event->pos().ry() - curSelecChartPos.ry());
                event->accept();
            }
        }break;
    }
}

void FlowChart::mouseReleaseEvent(QMouseEvent *event)
{
    switch(mouseEventType)
    {
        case MOUSE_EVENT_TYPE::CREATING_CNANGE_SIZE:
        {
            //curPaintChart->updatePath();
            resetPaintChartType();
            if(curSelecChart->chartType == PaintChartType::LINE)
            {
                Chart_Line *cl = reinterpret_cast<Chart_Line *>(curSelecChart);

                if(lineSelectChart)
                {
                    lineSelectChart->addMagiPointEndLine(magPointIndex,curSelecChart);
                    lineSelectChart->hideMagOnly();
                    cl->setEndChart(lineSelectChart);
                    cl->setEndMagIndex(magPointIndex);
                    cl->setEndDirect(lineSelectChart->getMagiPointDirect(magPointIndex));
                    cl->update();
                    lineSelectChart = nullptr;
                }
                else{
                    cl->resetEndChart();
                }

            }
            curPaintChart = nullptr;
            mouseEventType = MOUSE_EVENT_TYPE::NONE;
            setFileSetSaved(false);
            event->accept();
        }break;
        case MOUSE_EVENT_TYPE::RUNTIME_CHANGE_SIZE:
        {
            if(curSelecChart->chartType == PaintChartType::LINE)
            {
                Chart_Line *cl = reinterpret_cast<Chart_Line *>(curSelecChart);
                if(lineSelectChart)
                {
                    if(sizePointDirect == ORIENTION::STARTPOINT)
                    {
                        cl->resetStartChart();
                        lineSelectChart->addMagiPointStartLine(magPointIndex,curSelecChart);
                        lineSelectChart->hideMagOnly();
                        cl->setStartChart(lineSelectChart);
                        cl->setStartMagIndex(magPointIndex);
                        cl->setStartDirect(lineSelectChart->getMagiPointDirect(magPointIndex));
                    }else if(sizePointDirect == ORIENTION::ENDPOINT)
                    {
                        cl->resetEndChart();
                        lineSelectChart->addMagiPointEndLine(magPointIndex,curSelecChart);
                        lineSelectChart->hideMagOnly();
                        cl->setEndChart(lineSelectChart);
                        cl->setEndMagIndex(magPointIndex);
                        cl->setEndDirect(lineSelectChart->getMagiPointDirect(magPointIndex));
                    }else{
                        qDebug()<<"Error";
                    }

                    cl->update();
                }else
                {
                    if(sizePointDirect == ORIENTION::STARTPOINT)
                    {
                        cl->resetStartChart();
                    }else if(sizePointDirect == ORIENTION::ENDPOINT)
                    {
                        cl->resetEndChart();
                    }else
                    {
                        qDebug()<<"Error";
                    }
                }
            }
            mouseEventType = MOUSE_EVENT_TYPE::NONE;
            lineSelectChart = nullptr;
            setFileSetSaved(false);
            event->accept();
        }break;
        case MOUSE_EVENT_TYPE::RUNTIME_CREATE_MAGPOINT:
        {
            if(newLineToSelectChart)
            {
                newLineToSelectChart->addMagiPointEndLine(magPointToIndex,newLineChart);
                newLineToSelectChart->hideMagOnly();
                newLineChart->setEndChart(newLineToSelectChart);
                newLineChart->setEndMagIndex(magPointToIndex);
                newLineChart->setEndDirect(newLineToSelectChart->getMagiPointDirect(magPointToIndex));
                newLineChart->update();
            }else
            {
                if(newLineChart)
                    newLineChart->resetEndChart();
            }
            mouseEventType = MOUSE_EVENT_TYPE::NONE;
            newLineChart = nullptr;
            newLineFromSelectChart = nullptr;
            newLineToSelectChart = nullptr;
            setFileSetSaved(false);
            event->accept();
        }break;
        case MOUSE_EVENT_TYPE::RUNTIME_CHANGE_POS:
        {
            mouseEventType = MOUSE_EVENT_TYPE::NONE;
            setFileSetSaved(false);
            event->accept();
        }break;
        default:case MOUSE_EVENT_TYPE::NONE:
        {
            event->ignore();
        }break;
    }

}

void FlowChart::keyPressEvent(QKeyEvent *ev)
{
    ev->ignore();
    switch(ev->key())
    {
        case Qt::Key_Escape:
        {
            if(curSelecChart)
            {
                curSelecChart->hideMagSize();
                curSelecChart = nullptr;
            }
        }break;
        case Qt::Key_Delete:
        {
            if(curSelecChart)
            {
                if(curSelecChart->chartType == PaintChartType::LINE)
                {
                    if(!delLine(curSelecChart))
                    {
                        qDebug()<<"Error";
                    }
                }else{
                    if(!delChart(curSelecChart))
                    {
                        qDebug()<<"Error";
                    }
                }
                curSelecChart = nullptr;

            }
        }break;
#if 0
        case Qt::Key_Q:
        {
            qDebug()<<"总个数：charts:"<<charts.size()<<",lines:"<<line.size();
            for(auto it = charts.begin();it != charts.end();it++)
            {
                qDebug()<<"\t磁力点个数："<<(*it)->magPoint.i_point.size();
                for(auto magit = (*it)->magPoint.i_point.begin();magit!=(*it)->magPoint.i_point.end();magit++)
                {
                    qDebug()<<"\t\t线头个数："<<(*magit)->i_lineStart.size()<<"，线尾个数："<<(*magit)->i_lineEnd.size();
                    for(auto magLineStIt = (*magit)->i_lineStart.begin();magLineStIt != (*magit)->i_lineStart.end();magLineStIt++)
                    {
                        qDebug()<<"\t\t\t线头ID："<<(*magLineStIt)->getID();
                    }
                    for(auto magLineEnIt = (*magit)->i_lineEnd.begin();magLineEnIt != (*magit)->i_lineEnd.end();magLineEnIt++)
                    {
                        qDebug()<<"\t\t\t线尾ID："<<(*magLineEnIt)->getID();
                    }
                }
            }
            qDebug();
            for(auto it = line.begin();it != line.end();it++)
            {
                qDebug()<<"\t线头："<<((dynamic_cast<Chart_Line*>(*it)->getStartChart() == nullptr)?"-":"有")<<"，线尾："<<(((dynamic_cast<Chart_Line*>(*it)->getEndChart()) == nullptr)?"-":"有");
            }
        }break;
#endif
        default:{
            ev->ignore();
        }
    }
}

void FlowChart::keyReleaseEvent(QKeyEvent *ev)
{
    ev->ignore();
}
