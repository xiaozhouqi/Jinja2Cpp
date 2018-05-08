#include "filters.h"
#include "value_visitors.h"

#include <algorithm>

namespace jinja2
{
namespace filters
{

bool FilterBase::ParseParams(const std::initializer_list<ArgumentInfo>& argsInfo, const CallParams& params)
{
    bool result = true;
    m_args = helpers::ParseCallParams(argsInfo, params, result);

    return result;
}

Join::Join(FilterParams params)
{
    ParseParams({{"d", false, std::string()}, {"attribute"}}, params);
}

Value Join::Filter(const Value& baseVal, RenderContext& context)
{
    if (!baseVal.isList())
        return Value();

    auto attrExpr = m_args["attribute"];
    Value attrName = attrExpr ? attrExpr->Evaluate(context) : Value();

    ValuesList values = boost::apply_visitor(visitors::ListEvaluator(attrName), baseVal.data());

    bool isFirst = true;
    Value result;
    Value delimiter = m_args["d"]->Evaluate(context);
    for (const Value& val : values)
    {
        if (isFirst)
            isFirst = false;
        else
            result = boost::apply_visitor(visitors::StringJoiner(), result.data(), delimiter.data());

        result = boost::apply_visitor(visitors::StringJoiner(), result.data(), val.data());
    }

    return result;
}

Sort::Sort(FilterParams params)
{
    ParseParams({{"reverse", false, Value(false)}, {"case_sensitive", false, Value(false)}, {"attribute", false}}, params);
}

Value Sort::Filter(const Value& baseVal, RenderContext& context)
{
    auto attrExpr = m_args["attribute"];
    auto isReverseExpr = m_args["reverse"];
    auto isCsExpr = m_args["case_sensitive"];
    Value attrName = attrExpr ? attrExpr->Evaluate(context) : Value();
    Value isReverseVal = isReverseExpr ? isReverseExpr->Evaluate(context) : Value(false);
    Value isCsVal = isCsExpr ? isCsExpr->Evaluate(context) : Value(false);

    ValuesList values = Apply<visitors::ListEvaluator>(baseVal);
    BinaryExpression::Operation oper =
            Apply<visitors::BooleanEvaluator>(isReverseVal) ? BinaryExpression::LogicalGt : BinaryExpression::LogicalLt;
    BinaryExpression::CompareType compType =
            Apply<visitors::BooleanEvaluator>(isCsVal) ? BinaryExpression::CaseSensitive : BinaryExpression::CaseInsensitive;

    std::sort(values.begin(), values.end(), [&attrName, oper, compType](auto& val1, auto& val2) {
        Value cmpRes;
        if (attrName.isEmpty())
            cmpRes = boost::apply_visitor(visitors::BinaryMathOperation(oper, compType), val1.data(), val2.data());
        else
            cmpRes = boost::apply_visitor(visitors::BinaryMathOperation(oper, compType), val1.subscript(attrName).data(), val2.subscript(attrName).data());

        return Apply<visitors::BooleanEvaluator>(cmpRes);
    });

    return values;
}

Attribute::Attribute(FilterParams params)
{

}

Value Attribute::Filter(const Value& baseVal, RenderContext& context)
{
    return Value();
}

Default::Default(FilterParams params)
{

}

Value Default::Filter(const Value& baseVal, RenderContext& context)
{
    return Value();
}

DictSort::DictSort(FilterParams params)
{

}

Value DictSort::Filter(const Value& baseVal, RenderContext& context)
{
    return Value();
}

GroupBy::GroupBy(FilterParams params)
{

}

Value GroupBy::Filter(const Value& baseVal, RenderContext& context)
{
    return Value();
}

Map::Map(FilterParams params)
{

}

Value Map::Filter(const Value& baseVal, RenderContext& context)
{
    return Value();
}

PrettyPrint::PrettyPrint(FilterParams params)
{

}

Value PrettyPrint::Filter(const Value& baseVal, RenderContext& context)
{
    return Value();
}

Random::Random(FilterParams params)
{

}

Value Random::Filter(const Value& baseVal, RenderContext& context)
{
    return Value();
}

SequenceAccessor::SequenceAccessor(FilterParams params, SequenceAccessor::Mode mode)
{

}

Value SequenceAccessor::Filter(const Value& baseVal, RenderContext& context)
{
    return Value();
}

Serialize::Serialize(FilterParams params, Serialize::Mode mode)
{

}

Value Serialize::Filter(const Value& baseVal, RenderContext& context)
{
    return Value();
}

Slice::Slice(FilterParams params, Slice::Mode mode)
{

}

Value Slice::Filter(const Value& baseVal, RenderContext& context)
{
    return Value();
}

StringConverter::StringConverter(FilterParams params, StringConverter::Mode mode)
{

}

Value StringConverter::Filter(const Value& baseVal, RenderContext& context)
{
    return Value();
}

StringFormat::StringFormat(FilterParams params, StringFormat::Mode mode)
{

}

Value StringFormat::Filter(const Value& baseVal, RenderContext& context)
{
    return Value();
}

Tester::Tester(FilterParams params, Tester::Mode mode)
{

}

Value Tester::Filter(const Value& baseVal, RenderContext& context)
{
    return Value();
}

ValueConverter::ValueConverter(FilterParams params, ValueConverter::Mode mode)
{

}

Value ValueConverter::Filter(const Value& baseVal, RenderContext& context)
{
    return Value();
}


} // filters
} // jinja2
