
namespace MenerwaProvider.Interfaces
{
    public interface IProvider
    {
        string GetData(string id, string separator);
        int Count();
    }
}
