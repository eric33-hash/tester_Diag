#include "load_odx_d.h"

#include <iostream>
#include <QDebug>
#include <QFile>

LoadODX_D::LoadODX_D()
{
    doc_ptr_ = std::make_unique<pugi::xml_document>();
}
LoadODX_D::~LoadODX_D()
{

}
ODX_D LoadODX_D::load(const QString fileName)
{
//    QFile file(fileName);
//    QByteArray fileData;
//    if(!file.open(QIODevice::ReadOnly))
//    {
//        std::cout << "odx-d open content failed!" << std::endl;

//    }
//    fileData = file.readAll();
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(fileName.toLatin1().data());

    //pugi::xml_parse_result result = doc_ptr_->load_file(&fileName);
    //pugi::xml_parse_result result = doc_ptr_->load_buffer(&fileData, fileData.length());
    if (!result) {
        std::cout << "LoadIndex load content failed!" << std::endl;

    }

    // Access the root node: FLASH
    pugi::xml_node root = doc.child("ODX");

    ODX_D dd;
    read_odx(root, dd);
    return dd;
}

void LoadODX_D::print()
{
    qDebug() << QString("odx-v property:{xmlns:xsi:%1 MODEL-VERSION:%2 xsi:noNamespaceSchemaLocation:%3}").
                arg(odx_.attr_xmlns_xsi, odx_.attr_model_version).arg(odx_.attr_xsi_noNamespaceSchemaLocation);

}

int LoadODX_D::read_odx(const pugi::xml_node &node, ODX_D &data)
{
    int result = 0;
    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
        if (strcmp(attr.name(), "xmlns:xsi") == 0) {
            data.attr_xmlns_xsi = attr.value();
        } else if (strcmp(attr.name(), "MODEL-VERSION") == 0) {
            data.attr_model_version = attr.value();
        } else if (strcmp(attr.name(), "xsi:noNamespaceSchemaLocation") == 0) {
            data.attr_xsi_noNamespaceSchemaLocation = attr.value();
        }
    }

    for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {

        if (strcmp(child.name(), "DIAG-LAYER-CONTAINER") == 0) {
            for (pugi::xml_node diagNode = child.first_child(); diagNode; diagNode = diagNode.next_sibling())
            {
                if(strcmp(diagNode.name(), "BASE-VARIANTS") == 0)
                {
                    ECU_VARIANT ecu;
                    for (pugi::xml_node BaseNode = diagNode.first_child().first_child(); BaseNode; BaseNode = BaseNode.next_sibling())
                    {
                        ecu.attr_id = BaseNode.attribute("ID").value();
                        if(strcmp(BaseNode.name(), "SHORT-NAME") == 0)
                        {
                            ecu.child_short_name = BaseNode.child_value();
                        }
                        else if(strcmp(BaseNode.name(), "FUNCT-CLASSS") == 0)
                        {
                            for (pugi::xml_node serviceNode = BaseNode.first_child(); serviceNode; serviceNode = serviceNode.next_sibling())
                            {
                                FUNCCLASS func;
                                func.child_short_name = serviceNode.first_attribute().value();
                                ecu.child_funclass.child_funclass.append(func);
                            }

                        }
                        else if(strcmp(BaseNode.name(),"DIAG-COMMS") == 0)
                        {
                            for (pugi::xml_node serviceNode = BaseNode.first_child(); serviceNode; serviceNode = serviceNode.next_sibling())
                            {
                                DIAG_COMM diagcomm;
                                diagcomm.attr_id = serviceNode.first_attribute().value();
                                for(pugi::xml_node diagcommNode = serviceNode.first_child(); diagcommNode; diagcommNode = diagcommNode.next_sibling())
                                {
                                    if(strcmp(diagcommNode.name(),"SHORT-NAME") == 0)
                                    {
                                        diagcomm.child_short_name = diagcommNode.child_value();
                                    }
                                    else if(strcmp(diagcommNode.name(),"FUNCT-CLASS-REFS") == 0)
                                    {
                                        diagcomm.FUNCTCLASS_REF = diagcommNode.first_child().first_attribute().value();
                                    }
                                    else if(strcmp(diagcommNode.name(),"REQUEST-REF") ==0)
                                    {
                                        diagcomm.REQUEST_REF = diagcommNode.first_attribute().value();
                                    }
                                    else if(strcmp(diagcommNode.name(),"POS-RESPONSE-REFS") == 0)
                                    {
                                        for(pugi::xml_node posrefNode = diagcommNode.first_child(); posrefNode; posrefNode = posrefNode.next_sibling())
                                        {
                                            diagcomm.POS_RESPONSE_REFS.append(posrefNode.first_attribute().value());
                                        }
                                    }
                                    else if(strcmp(diagcommNode.name(),"NEG-RESPONSE-REFS") == 0)
                                    {
                                        for(pugi::xml_node negrefNode = diagcommNode.first_child(); negrefNode; negrefNode = negrefNode.next_sibling())
                                        {
                                            diagcomm.NEG_RESPONSE_REFS.append(negrefNode.first_attribute().value());
                                        }
                                    }
                                }
                                ecu.child_diag_comms.child_DIAGCOMM.append(diagcomm);
                            }
                        }
                        else if(strcmp(BaseNode.name(),"REQUESTS") == 0)
                        {
                            for (pugi::xml_node serviceNode = BaseNode.first_child(); serviceNode; serviceNode = serviceNode.next_sibling())
                            {
                                REQUEST request;
                                request.attr_id = serviceNode.first_attribute().value();
                                for (pugi::xml_node RequestNode = serviceNode.first_child(); RequestNode; RequestNode = RequestNode.next_sibling())
                                {
                                    if(strcmp(RequestNode.name(),"SHORT-NAME") == 0)
                                    {
                                        request.child_short_name = RequestNode.child_value();
                                    }
                                    else if(strcmp(RequestNode.name(),"LONG-NAME") == 0)
                                    {
                                        request.child_long_name = RequestNode.child_value();
                                    }
                                    else if(strcmp(RequestNode.name(),"PARAMS") == 0)
                                    {
                                        for(pugi::xml_node ParamNodes = RequestNode.first_child(); ParamNodes; ParamNodes = ParamNodes.next_sibling())
                                        {
                                            PARAM prama;
                                            for (pugi::xml_attribute attrpara = ParamNodes.first_attribute(); attrpara; attrpara = attrpara.next_attribute()) {
                                                if (strcmp(attrpara.name(), "xsi:type") == 0) {
                                                    prama.attr_xsi_type = attrpara.value();
                                                } else if (strcmp(attrpara.name(), "SEMANTIC") == 0) {
                                                    prama.attr_semantic = attrpara.value();
                                                }
                                            }
                                            for (pugi::xml_node ParamNode = ParamNodes.first_child(); ParamNode; ParamNode = ParamNode.next_sibling())
                                            {
                                                if(strcmp(ParamNode.name(),"SHORT-NAME") == 0)
                                                {
                                                    prama.child_short_name = ParamNode.child_value();
                                                }
                                                else if(strcmp(ParamNode.name(),"LONG-NAME") == 0)
                                                {
                                                    prama.child_long_name.data_value = ParamNode.child_value();
                                                }
                                                else if(strcmp(ParamNode.name(),"BYTE-POSITION") == 0)
                                                {
                                                    prama.child_byte_position.data_value = ParamNode.child_value();
                                                }
                                                else if(strcmp(ParamNode.name(),"CODED-VALUE") == 0)
                                                {
                                                    prama.child_coded_value.data_value = ParamNode.child_value();
                                                }
                                                else if(strcmp(ParamNode.name(),"DIAG-CODED-TYPE") == 0)
                                                {
                                                    prama.child_diag_coded_type.attr_base_data_type = ParamNode.first_attribute().value();
                                                    prama.child_diag_coded_type.attr_xsi_type = ParamNode.first_attribute().next_attribute().value();
                                                    prama.child_diag_coded_type.child_bit_length = ParamNode.first_child().child_value();
                                                }
                                                else if(strcmp(ParamNode.name(),"TABLE-ROW-REF") == 0)
                                                {
                                                    prama.child_table_row_ref = ParamNode.first_attribute().value();
                                                }
                                                else if(strcmp(ParamNode.name(),"DOP-REF") == 0)
                                                {
                                                    prama.child_dop_ref = ParamNode.first_attribute().value();
                                                }
                                            }
                                            request.child_params.child_param.append(prama);
                                        }
                                    }
                                }
                                ecu.child_request.child_request.append(request);
                            }
                        }
                        else if(strcmp(BaseNode.name(),"DIAG-DATA-DICTIONARY-SPEC") == 0)
                        {
                            for (pugi::xml_node DiagDictionaryNode = BaseNode.first_child(); DiagDictionaryNode; DiagDictionaryNode = DiagDictionaryNode.next_sibling())
                            {
                                if(strcmp(DiagDictionaryNode.name(),"TABLES") == 0)
                                {
                                    for (pugi::xml_node TableNode = DiagDictionaryNode.first_child(); TableNode; TableNode = TableNode.next_sibling())
                                    {
                                           TABLE table;
                                           table.attr_id = TableNode.first_attribute().value();
                                           qDebug() << "table.attr_id =" << table.attr_id;
                                           for (pugi::xml_node TableContentNode = TableNode.first_child(); TableContentNode; TableContentNode = TableContentNode.next_sibling())
                                           {
                                               if(strcmp(TableContentNode.name(),"SHORT-NAME") == 0)
                                               {
                                                   table.child_short_name = TableContentNode.child_value();
                                               }
                                               else if(strcmp(TableContentNode.name(),"KEY-DOP-REF") == 0)
                                               {
                                                   table.child_key_drop_ref.attr_id_ref = TableContentNode.first_attribute().value();
                                               }
                                               else if(strcmp(TableContentNode.name(),"TABLE-ROW") == 0)
                                               {
                                                   TABLE_ROW tablerow;
                                                   tablerow.attr_id = TableContentNode.first_attribute().value();
                                                   for (pugi::xml_node TableRowNode = TableContentNode.first_child(); TableRowNode; TableRowNode = TableRowNode.next_sibling())
                                                   {
                                                       if(strcmp(TableRowNode.name(),"SHORT-NAME") == 0)
                                                       {
                                                           tablerow.child_short_name = TableRowNode.child_value();
                                                       }
                                                       else if(strcmp(TableRowNode.name(),"KEY") == 0)
                                                       {
                                                           tablerow.child_key = TableRowNode.child_value();
                                                       }
                                                       else if(strcmp(TableRowNode.name(),"STRUCTURE-REF") == 0)
                                                       {
                                                           tablerow.child_structure_ref = TableRowNode.attribute("ID-REF").value();
                                                       }
                                                   }
                                                   table.child_table_row.append(tablerow);
                                               }
                                           }
                                           ecu.child_diag_data_dictionary_spec.child_tables.child_table.append(table);
                                    }
                                }
                                else if(strcmp(DiagDictionaryNode.name(),"STRUCTURES") == 0)
                                {
                                    for (pugi::xml_node structureNode = DiagDictionaryNode.first_child(); structureNode; structureNode = structureNode.next_sibling())
                                    {
                                        STRUCTURE structure;
                                        structure.attr_id = structureNode.first_attribute().value();
                                        qDebug() << "structure.attr_id =" << structure.attr_id;
                                        for (pugi::xml_node structureContentNode = structureNode.first_child(); structureContentNode; structureContentNode = structureContentNode.next_sibling())
                                        {
                                            if(strcmp(structureContentNode.name(),"SHORT-NAME") == 0)
                                            {
                                                structure.child_short_name = structureContentNode.child_value();
                                            }
                                            else if(strcmp(structureContentNode.name(),"BYTE-SIZE") == 0)
                                            {
                                                structure.byte_size = structureContentNode.child_value();
                                            }
                                            else if(strcmp(structureContentNode.name(),"BYTE-POSITION") == 0)
                                            {
                                                structure.byte_position = structureContentNode.child_value();
                                            }
                                            else if(strcmp(structureContentNode.name(),"PARAMS") == 0)
                                            {
                                                for (pugi::xml_node paramNode = structureContentNode.first_child(); paramNode; paramNode = paramNode.next_sibling())
                                                {
                                                    PARAM param;
                                                    for (pugi::xml_attribute attrpara = paramNode.first_attribute(); attrpara; attrpara = attrpara.next_attribute()) {
                                                        if (strcmp(attrpara.name(), "xsi:type") == 0) {
                                                            param.attr_xsi_type = attrpara.value();
                                                        } else if (strcmp(attrpara.name(), "SEMANTIC") == 0) {
                                                            param.attr_semantic = attrpara.value();
                                                        }
                                                    }
                                                    for (pugi::xml_node Node = paramNode.first_child(); Node; Node = Node.next_sibling())
                                                    {
                                                        if(strcmp(Node.name(),"SHORT-NAME") == 0)
                                                        {
                                                            param.child_short_name = Node.child_value();
                                                        }
                                                        else if(strcmp(Node.name(),"LONG-NAME") == 0)
                                                        {
                                                            param.child_long_name.data_value = Node.child_value();
                                                        }
                                                        else if(strcmp(Node.name(),"BYTE-POSITION") == 0)
                                                        {
                                                            param.child_byte_position.data_value = Node.child_value();
                                                        }
                                                        else if(strcmp(Node.name(),"PHYS-CONSTANT-VALUE") == 0)
                                                        {
                                                            param.child_coded_value.data_value = Node.child_value();
                                                        }
                                                        else if(strcmp(Node.name(),"DOP-REF") == 0)
                                                        {
                                                            param.child_dop_ref = Node.first_attribute().value();
                                                        }
                                                    }
                                                    structure.child_params.child_param.append(param);
                                                }
                                            }
                                        }
                                        ecu.child_diag_data_dictionary_spec.child_structures.child_structure.append(structure);
                                    }
                                }
                                else if(strcmp(DiagDictionaryNode.name(),"DATA-OBJECT-PROPS") == 0)
                                {
                                    for (pugi::xml_node DOPNode = DiagDictionaryNode.first_child(); DOPNode; DOPNode = DOPNode.next_sibling())
                                    {
                                        DATA_OBJECT_PROP dop;
                                        dop.attr_id = DOPNode.first_attribute().value();
                                        qDebug() << "dop.attr_id =" << dop.attr_id;
                                        for (pugi::xml_node DOPContentNode = DOPNode.first_child(); DOPContentNode; DOPContentNode = DOPContentNode.next_sibling())
                                        {
                                            if(strcmp(DOPContentNode.name(),"SHORT-NAME") == 0)
                                            {
                                                dop.child_short_name = DOPContentNode.child_value();
                                            }
                                            else if(strcmp(DOPContentNode.name(),"COMPU-METHOD") == 0)
                                            {
                                                dop.child_compu_method = DOPContentNode.child("CATEGORY").child_value();
                                            }
                                            else if(strcmp(DOPContentNode.name(),"DIAG-CODED-TYPE") == 0)
                                            {
                                                dop.child_diag_coded_type.attr_base_type_encoding = DOPContentNode.attribute("BASE-TYPE-ENCODING").value();
                                                dop.child_diag_coded_type.attr_base_data_type = DOPContentNode.attribute("BASE-DATA-TYPE").value();
                                                dop.child_diag_coded_type.attr_xsi_type = DOPContentNode.attribute("xsi:type").value();
                                                dop.child_diag_coded_type.child_bit_length = DOPContentNode.child("BIT-LENGTH").child_value();
                                            }
                                            else if(strcmp(DOPContentNode.name(),"PHYSICAL-TYPE") == 0)
                                            {
                                                dop.child_physical_type.attr_base_data_type = DOPContentNode.attribute("BASE-DATA-TYPE").value();
                                            }
                                        }
                                        ecu.child_diag_data_dictionary_spec.child_data_object_props.child_data_object_prop.append(dop);
                                    }
                                }
                            }
                        }
                    }
                    data.child_diag_layer_container.child_ecu_variants.child_ecu_variant.append(ecu);
                }
            }
        }
       //
    }

    return result;
}
