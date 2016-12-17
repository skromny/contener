
using AxProjects.Data;
using AxProjects.Models;
using AxProjects.Models.Partner;
using MenerwaProvider.Interfaces;
using System.Text;

namespace MenervaProvider.Customers
{
    public class Provider : IProvider
    {
        static AnUserSession session;

        public Provider()
        {
            AnSoaServiceInfo serviceInfo;
            string message;

            AnBaseContractClient baseClient = new AnBaseContractClient("BasicHttpBinding_IAnBaseContract");

            AnSoaOperationResult rs = baseClient.StartSession("admin", "wodaMineralna", new AnSoaClientInfo(), out session, out serviceInfo, out message);


        }

        public int Count()
        {
            int total;
            string message;
            //AnCustomerListViewModel[] model;
            AnCustomerModel[] model;


            AnPartnerContractClient partnerClient = new AnPartnerContractClient();
            AnDataViewParameters dvParams = new AnDataViewParameters();
            
            dvParams.Filters = new AnDataViewFilterEntry[] { new AnDataViewFilterEntry() { FieldName = "State", IntValue = 0 } };

            AnSoaOperationResult rs = partnerClient.GetCustomers(session.SessionId, dvParams, out model, out message, out total);
            //AnSoaOperationResult rs = partnerClient.GetCustomerListView(session.SessionId, dvParams, out model, out message, out total);

            if (rs == AnSoaOperationResult.Success)
                return total;

            return -1;
        }

        public string GetData(string id, string separator)
        {
            int total;
            string message;
            AnCustomerModel[] model;


            AnPartnerContractClient partnerClient = new AnPartnerContractClient();
            AnDataViewParameters dvParams = new AnDataViewParameters();
            dvParams.Filters = new AnDataViewFilterEntry[] {
                new AnDataViewFilterEntry() { FieldName = "State", IntValue = 0 },
                new AnDataViewFilterEntry() { FieldName = "Id", IntValue = int.Parse(id) }
            };

            AnSoaOperationResult rs = partnerClient.GetCustomers(session.SessionId, dvParams, out model, out message, out total);

            if (rs == AnSoaOperationResult.Success) {
                if (total > 0)
                {
                    StringBuilder sb = new StringBuilder();
                    sb.Append(model[0].Id);
                    sb.Append(separator);
                    sb.Append(model[0].Name);
                    sb.Append(separator);
                    sb.Append(model[0].FullName);
                    sb.Append(separator);
                    sb.Append(model[0].Description);
                    sb.Append(separator);
                    sb.Append(model[0].NIP);
                    sb.Append(separator);
                    sb.Append(model[0].REGON);
                    sb.Append(separator);
                    sb.Append(model[0].WebSites);

                    return sb.ToString();
                }
            }

            return null;
        }
    }
}
